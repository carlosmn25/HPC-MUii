#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
#define A_FILAS 1000
#define A_COLUMNAS 1000
#define B_FILAS 1000
#define B_COLUMNAS 1000
*/

int main(int argc, char *argv[]) {
    int i, j, k;
    int A_FILAS, A_COLUMNAS, B_FILAS, B_COLUMNAS;
    
    if(argc != 5) {
        printf("Uso: %s <A_FILAS> <A_COLUMNAS> <B_FILAS> <B_COLUMNAS>\n)", argv[0]);
        exit(1);
    }

    A_FILAS = atoi(argv[1]);
    A_COLUMNAS = atoi(argv[2]);
    B_FILAS = atoi(argv[3]);
    B_COLUMNAS = atoi(argv[4]);

    printf("%d %d %d %d\n", A_FILAS, A_COLUMNAS, B_FILAS, B_COLUMNAS);

    //int A[A_FILAS][A_COLUMNAS], B[B_FILAS][B_COLUMNAS], C[A_FILAS][B_COLUMNAS];
    //initialize the matrixes with malloc
    int *A = (int *)malloc(A_FILAS * A_COLUMNAS * sizeof(int));
    int *B = (int *)malloc(B_FILAS * B_COLUMNAS * sizeof(int));
    int *C = (int *)malloc(A_FILAS * B_COLUMNAS * sizeof(int));

    if(A == NULL || B == NULL || C == NULL) {
        printf("Error: No se pudo reservar memoria para las matrices\n");
        exit(1);
    }

    if(A_COLUMNAS != B_FILAS) {
        printf("No se pueden multiplicar las matrices\n");
        exit(2);
    }

    for (i = 0; i < A_FILAS; i++) {
        for (j = 0; j < A_COLUMNAS; j++) {
            A[A_COLUMNAS*i + j] = i + j;
        }
    }

    for (i = 0; i < B_FILAS; i++) {
        for (j = 0; j < B_COLUMNAS; j++) {
            B[B_COLUMNAS*i + j] = i - j;
        }
    }

    for (i = 0; i < A_FILAS; i++) {
        for (j = 0; j < B_COLUMNAS; j++) {
            C[B_COLUMNAS*i + j] = 0;
        }
    }

    clock_t start = clock();

    //Multiplicacion de matrices ijk
    for (i = 0; i < A_FILAS; i++) {
        for (j = 0; j < A_COLUMNAS; j++) {
            for (k = 0; k < B_COLUMNAS; k++) {
                //C[i] += A[i] * B[k];
                C[B_COLUMNAS*i + k] += A[A_COLUMNAS*i + j] * B[B_COLUMNAS*j + k];
            }
        }
    }

    clock_t end = clock();

    //Imprime la matriz C
    
    /*for (i = 0; i < A_FILAS; i++) {
        for (j = 0; j < B_COLUMNAS; j++) {
            printf("%d \t", C[B_COLUMNAS*i + j]);
        }
        printf("\n");
    }*/

    printf("Tiempo de ejecucion: %f segundos \n", (double)(end - start) / CLOCKS_PER_SEC);

    clock_t start2 = clock();

    //Multiplicacion de matrices jki
    for (j = 0; j < A_COLUMNAS; j++) {
        for (k = 0; k < B_COLUMNAS; k++) {
            for (i = 0; i < A_FILAS; i++) {
                //C[i] += A[i] * B[k];
                C[B_COLUMNAS*i + k] += A[A_COLUMNAS*i + j] * B[B_COLUMNAS*j + k];
            }
        }
    }

    clock_t end2 = clock();

    printf("Tiempo de ejecucion: %f segundos \n", (double)(end2 - start2) / CLOCKS_PER_SEC);

    clock_t start3 = clock();

    //Multiplicacion de matrices kji
    for (k = 0; k < B_COLUMNAS; k++) {
        for (j = 0; j < A_COLUMNAS; j++) {
            for (i = 0; i < A_FILAS; i++) {
                //C[i] += A[i] * B[k];
                C[B_COLUMNAS*i + k] += A[A_COLUMNAS*i + j] * B[B_COLUMNAS*j + k];
            }
        }
    }

    clock_t end3 = clock();

    printf("Tiempo de ejecucion: %f segundos \n", (double)(end3 - start3) / CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(C);

    return 0;
}