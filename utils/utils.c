#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

// returns the actual time in seconds
double dwalltime(){
    double sec;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    sec = tv.tv_sec + tv.tv_usec / 1000000.0;
    return sec;
}

//prints a matrix os size N
void print_matrix(double* M , int N){
    printf("\n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%f ", M[i*N+j]);
        }
        printf("\n");
    }
}

void print_arr(int *arr, int N){
    printf("\n");
    for (int i = 0; i < N; i++){
        printf("%d,",arr[i]);
    }
    printf("\n");
}

void random_arr(int *arr, int N){
    srand(time(NULL));
    for (int i = 0; i < N; i++){
        arr[i] = rand()%100;
    }
}
