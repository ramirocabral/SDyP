#include <stdio.h>
#include <stdlib.h>
#include "../../utils/utils.h"

void print_matrix(double* M , int N);

int main(int argc,char*argv[]) {
    int N;

    if ((argc != 2) || ((N = atoi(argv[1])) <= 0) ){
        printf("\nUsar: %s n\n  n: Dimension de la matriz (nxn X nxn)\n", argv[0]);
        exit(1);
    }

    //L: matriz triangular inferior
    //U: matriz triangular superior
    //M : matriz de NxN
    double *L = (double *)malloc(sizeof(double)*N*N);
    double *U = (double *)malloc(sizeof(double)*N*N);
    double *M = (double *)malloc(sizeof(double)*N*N);

    //Operaciones: MU, ML, UM, LM
    double *MU = (double *)malloc(sizeof(double)*N*N);
    double *ML = (double *)malloc(sizeof(double)*N*N);
    double *UM = (double *)malloc(sizeof(double)*N*N);
    double *LM = (double *)malloc(sizeof(double)*N*N);

    //init matrices
    //U y L
    for (int i = 0; i < N; i++){
        //inicializar U
        for (int j = i; j < N; j++){
            U[i*N + j] = 1;
        }
        for (int j = 0; j < i+1; j++){
            L[i*N + j] = 1;
        }
    }
    //M
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            M[i*N + j] = 1;
        }
    }

    double timetick = dwalltime();

    //multiplicaciones

    int k;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            MU[i*N + j] = 0;
            for (k = 0; k < j+1; k++){
                MU[i*N + j] += M[i*N + k] * U[k*N + j];
            }
            ML[i*N + j] = 0;
            for (k = j; k< N; k++){
                ML[i*N + j] += M[i*N + k] * L[k*N + j];
            }
            UM[i*N + j] = 0;
            for (k = i; k < N; k++){
                UM[i*N + j] += U[i*N + k] * M[k*N + j];
            }
            LM[i*N + j] = 0;
            for (k = 0; k < i+1; k++){
                LM[i*N + j] += L[i*N + k] * M[k*N + j];
            }
        }
    }

    printf("Tiempo en segundos ALMACENANDO CEROS: %f\n", dwalltime() - timetick);

    // print_matrix(M,N);
    // print_matrix(U,N);
    // print_matrix(MU,N);
    // print_matrix(ML,N);
    // print_matrix(UM,N);
    // print_matrix(LM,N);

    free(L);
    free(U);
    U = (double *)malloc(sizeof(double)*N*(N+1)/2);
    L = (double *)malloc(sizeof(double)*N*(N+1)/2);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            MU[i*N + j] = 0;
            ML[i*N + j] = 0;
            UM[i*N + j] = 0;
            LM[i*N + j] = 0;
        }
    }

    //inicializamos matrices triangulares
    for (int i = 0; i < N*(N+1)/2; i++){
        U[i] = 1;
        L[i] = 1;
    }

    timetick = dwalltime();
    
    //multiplicacion
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            MU[i*N + j] = 0;
            for (k = 0; k < j+1; k++){
                MU[i*N + j] += M[i*N + k] * U[k*N + j - k*(k+1)/2];
            }
            ML[i*N + j] = 0;
            for (k = j; k< N; k++){
                ML[i*N + j] += M[i*N + k] * L[j + k*(i+1)/2];
            }
            UM[i*N + j] = 0;
            for (k = i; k < N; k++){
                UM[i*N + j] += U[i*N + k - i*(i+1)/2] * M[k*N + j];
            }
            LM[i*N + j] = 0;
            for (k = 0; k < i+1; k++){
                LM[i*N + j] += L[i + k*(i+1)/2] * M[k*N + j];
            }
        }
    }

    printf("Tiempo en segundos SIN ALMACENAR CEROS: %f\n", dwalltime() - timetick);
    //
    // print_matrix(M,N);
    // print_matrix(U,N);
    // print_matrix(MU,N);
    // print_matrix(ML,N);
    // print_matrix(UM,N);
    // print_matrix(LM,N);
    //
    //
    free(M);
    free(MU);
    free(ML);
    free(UM);
    free(LM);

    return 0;
}

void print_matrix(double* M , int N){
    printf("\n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%f ", M[i*N+j]);
        }
        printf("\n");
    }
}
