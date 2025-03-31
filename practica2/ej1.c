#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../utils/utils.c"

int T, N;
double *A, *B, *C;

void *mult(void *arg){
    int id = *(int*)arg;

    int start = id * (N/T);
    int end = (id + 1) * (N/T);

    for (int i = start; i < end; i++){
        for (int j = 0; j < N; j++){
            double sum = 0;
            for (int k = 0; k < N; k++){
               sum += A[i*N + k]*B[k + j*N];
            }
            C[i*N + j] = sum;
        }
    }

    pthread_exit(NULL);
}

void verify(double *C, int size) {
    int i;
    for(i = 0; i < size*size; i++){
        if(C[i] != size) {
            printf("resultado incorrecto");
            break;
        }
    }
    printf("resultado correcto!");
}

void init_threads(pthread_t *threads, int *threadsIDs, int T){
    for (int id = 0; id < T; id++){
        threadsIDs[id] = id;
        pthread_create(&threads[id], NULL, &mult, (void*)&threadsIDs[id]);
    }
}

void wait_threads(pthread_t *threads, int T){
    for (int id = 0; id < T; id++){
        pthread_join(threads[id], NULL);
    }
}

int main(int argc, char* argv[]){
    if (argc < 3){
        fprintf(stderr, "parameters: [T: amount of threads], [N : size of the matrix]") ;
        return 1;
    }
    T = atoi(argv[1]);
    pthread_t threads[T];
    int threadsIDs[T];

    N = atoi(argv[2]);
    int i, j;

    // allocamos memoria para las matrices
    A = (double*)malloc(sizeof(double)*N*N);
    B = (double*)malloc(sizeof(double)*N*N);
    C = (double*)malloc(sizeof(double)*N*N);


    //inicializamos las matrices en 1
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            A[i*N+ j] = 1; 
            B[i*N + j] = 1; 
        }
    }

    //procesamiento secuencial
    double timetick = dwalltime();

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            double sum = 0;
            for (int k = 0; k < N; k++){
               sum += A[i*N + k]*B[k + j*N];
            }
            C[i*N + j] = sum;
        }
    }

    double secuencial = dwalltime() - timetick;

    printf("tiempo secuencial: %f\n", secuencial);

    for (int i = 0; i< N*N; i++) C[i] = 0;
    
    //procesamiento paralelo
    timetick = dwalltime();
    init_threads(threads, threadsIDs, T);

    wait_threads(threads, T);

    double paralelo = dwalltime() - timetick;

    printf("tiempo paralelo: %f\n", paralelo);

    verify(C, N);

    return 0;
}
