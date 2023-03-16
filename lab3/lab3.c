#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//Compilar con gcc -fopenmp lab3.c -o lab3.o

float MIN_TEMP = -10.0;
float MAX_TEMP = 50.0;
int DIAS = 365;

int main(int argc, char **argv) {
    //Obtain the number of years from the user
    if (argc != 2) {
        printf("Usage: %s <number of years>)\n", argv[0]);
    }
    int anyos = atoi(argv[1]);
    int np, pid;

    float *matrix = (float *) malloc(anyos * DIAS * sizeof(float));

    //Find the maximum temperature
    float maximum = MIN_TEMP;
    double start_t, end_t;

    start_t = omp_get_wtime();

    int i, j;

    if (pid == 0) {
        //Fill the matrix with random values (PARALELIZABLE)
        for (int i = 0; i < anyos; i++) {
            for (int j = 0; j < DIAS; j++) {
                matrix[DIAS*i + j] = ((float) rand() / (float) RAND_MAX) * MAX_TEMP + MIN_TEMP;
            }
        }
    }

    #pragma omp parallel for schedule(dynamic) shared(anyos, matrix) private(i,j) reduction(max : maximum) //num_threads(8)
    //Find the maximum temperature (PARALELIZABLE)
    for (i = 0; i < anyos; i++) {
        for (j = 0; j < DIAS; j++) {
            if (matrix[DIAS*i + j] > maximum) {
                maximum = matrix[DIAS*i + j];
            }
        }
    }

    end_t = omp_get_wtime();

    if (pid == 0) {
        printf("The maximum temperature is %f\n", maximum);
    	printf("Time: %f\n",end_t-start_t);
    }
}