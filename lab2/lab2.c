#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

float MIN_TEMP = -10.0;
float MAX_TEMP = 50.0;
int DIAS = 365;

int main(int argc, char **argv){
    //Obtain the number of years from the user
    if (argc != 2) {
        printf("Usage: %s <number of years>)\n", argv[0]);
    }
    int anyos = atoi(argv[1]);
    int np, pid;

    MPI_Init(&argc , &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    float *matrix = (float *) malloc(anyos * DIAS * sizeof(float));
    float *matrix_local = (float *) malloc(anyos/np * DIAS * sizeof(float));

    //Find the maximum temperature
    float max = MIN_TEMP;
    float max_local = MIN_TEMP;
    double start_t, end_t;

    if (pid == 0) {
        //Fill the matrix with random values
        for (int i = 0; i < anyos; i++) {
            for (int j = 0; j < DIAS; j++) {
                matrix[DIAS*i + j] = ((float) rand() / (float) RAND_MAX) * MAX_TEMP + MIN_TEMP;
            }
        }

        //Print the matrix
        /*for (int i = 0; i < anyos; i++) {
            for (int j = 0; j < DIAS; j++) {
                printf("%f ", matrix[DIAS*i + j]);
            }
            printf("\n");
        }
        printf("\n");*/
    }

    start_t = MPI_Wtime();    
    MPI_Scatter(matrix,DIAS*anyos/np,MPI_FLOAT,matrix_local,DIAS*anyos/np,MPI_FLOAT,0,MPI_COMM_WORLD);

    //Find the maximum temperature
    for (int i = 0; i < anyos/np; i++) {
        for (int j = 0; j < DIAS; j++) {
            if (matrix_local[DIAS*i + j] > max_local) {
                max_local = matrix_local[DIAS*i + j];
            }
            //if (pid == 0)
            //    printf("%f ", matrix_local[DIAS*i + j]);
        }
        //printf("\n");
    }

    printf("The maximum LOCAL temperature of Process %d is %f\n", pid, max_local);
    //MPI reduce with the maximum number of the matrix
    MPI_Reduce(&max_local, &max, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD);

    end_t = MPI_Wtime();
    MPI_Finalize();

    if(pid == 0) {
        printf("The maximum temperature is %f\n", max);
    	printf("Time: %f\n",end_t-start_t);
    }
}
