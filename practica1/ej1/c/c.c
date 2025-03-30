#include <stdio.h>
#include <stdlib.h>
#include "../../utils/utils.h"

int check(double *A, int N);

int main(int argc,char*argv[]) {

    int N;

    if ((argc != 2) || ((N = atoi(argv[1])) <= 0) ){
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }

    //tenemos que hacer A*A
    double *A = (double *)malloc(sizeof(double)*N*N);

    //A por filardas
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            A[i*N+j] = 1;
        }
    }

    double *B = (double *)malloc(sizeof(double)*N*N);

    double timetick = dwalltime();

    // multiplicacion
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            B[i*N+j] = 0;
            for (int k = 0; k < N; k++){
                B[i*N+j] += A[i*N+k]*A[k*N+j];
            }
        }
    }

    printf("Tiempo en segundos para matrices iguales %f\n", dwalltime() - timetick);

    if (check(B, N)){
        printf("Multiplicacion correcta\n");
    } else {
        printf("Multiplicacion incorrecta\n");
    }

    //Ahora con la segunda matriz A ordenada por columnas


    //tomamos en cuenta la construccion de la nueva matriz
    timetick = dwalltime();
    double* A_col = (double *)malloc(sizeof(double)*N*N);

    //A por columnas
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            A_col[j*N+i] = A[i*N+j];
        }
    }

    //multiplicacion

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            B[i*N+j] = 0;
            for (int k = 0; k < N; k++){
                B[i*N+j] += A[i*N+k]*A_col[k + j*N];
            }
        }
    }

    printf("Tiempo en segundos para matrices transpuestas %f\n", dwalltime() - timetick);

    if (check(B, N)){
        printf("Multiplicacion correcta\n");
    } else {
        printf("Multiplicacion incorrecta\n");
    }

    free(A);
    free(B);
    free(A_col);

    return 0;
}

int check(double *A, int N){
    int check = 1;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            check = check&&(A[i*N+j] == N);
        }
    }
    return check;
}
