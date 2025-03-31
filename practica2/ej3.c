#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils.c"

int T, N;
int *arr;
int min = INT_MAX, max = INT_MIN;

pthread_mutex_t min_mutex;
pthread_mutex_t max_mutex;

void *func(void *arg){
    int id = *(int*)arg;

    int start = id * (N/T);
    int end = (id + 1) * (N/T);
    int min_aux = INT_MAX, max_aux = INT_MIN;

    for (int i = start; i < end; i++){
        if (arr[i] < min_aux){
            min_aux = arr[i];
        }
        if (arr[i] > max_aux){
            max_aux = arr[i];
        }
    }

    pthread_mutex_lock(&min_mutex);
    if (min_aux < min){
        min = min_aux;
    }
    pthread_mutex_unlock(&min_mutex);
    pthread_mutex_lock(&max_mutex);
    if (max_aux > max){
        max = max_aux;
    }
    pthread_mutex_unlock(&max_mutex);

    pthread_exit(NULL);
}

void init_threads(pthread_t *threads, int *threadsIDs, int T){
    for (int id = 0; id < T; id++){
        threadsIDs[id] = id;
        pthread_create(&threads[id], NULL, &func, (void*)&threadsIDs[id]);
    }
}

void wait_threads(pthread_t *threads, int T){
    for (int id = 0; id < T; id++){
        pthread_join(threads[id], NULL);
    }
}

int main(int argc, char* argv[]){
    if (argc < 3){
        fprintf(stderr, "parameters: [T: amount of threads], [N : size of the array]") ;
        return 1;
    }

    T = atoi(argv[1]);
    pthread_t threads[T];
    int threadsIDs[T];

    N = atoi(argv[2]);

    srand(time(NULL));

    int i;
    arr = (int*)malloc(sizeof(int)*N);
    random_arr(arr, N);
    // print_arr(arr,N);

    int foo = INT_MAX, bar = INT_MIN;
    //procesamiento secuencial
    double timetick = dwalltime();

    for (i = 0; i < N; i++){
        if (arr[i] < foo){
            foo = arr[i];
        }
        if (arr[i] > bar){
            bar = arr[i];
        }
    }

    double seq = dwalltime() - timetick;

    printf("tiempo secuencial: %f\n", seq);
    printf("min: %d, max: %d\n", foo, bar);
    
    //procesamiento paralelo
    timetick = dwalltime();
    pthread_mutex_init(&min_mutex,NULL);
    pthread_mutex_init(&max_mutex,NULL);
    init_threads(threads, threadsIDs, T);

    wait_threads(threads, T);

    pthread_mutex_destroy(&min_mutex);
    pthread_mutex_destroy(&max_mutex);
    double parallel = dwalltime() - timetick;

    printf("tiempo paralelo: %f\n", parallel);
    printf("min: %d, max: %d\n", min, max);

    return 0;
}
