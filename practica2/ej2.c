#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils.c"

int T, N, X=5, ocurrences = 0;
int *arr;

pthread_mutex_t mutex;

void *func(void *arg){
    int id = *(int*)arg;

    int start = id * (N/T);
    int end = (id + 1) * (N/T);
    int aux = 0;

    for (int i = start; i < end; i++) if (arr[i] == X) aux++;

    pthread_mutex_lock(&mutex);
    ocurrences += aux;
    pthread_mutex_unlock(&mutex);

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


    int o = 0;
    //procesamiento secuencial
    double timetick = dwalltime();

    for (i = 0; i < N; i++) if (arr[i] == X) o++;

    double seq = dwalltime() - timetick;

    printf("tiempo secuencial: %f\n", seq);
    printf("ocurrencias: %d\n", o);
    
    //procesamiento paralelo
    timetick = dwalltime();
    pthread_mutex_init(&mutex,NULL);
    init_threads(threads, threadsIDs, T);

    wait_threads(threads, T);

    pthread_mutex_destroy(&mutex);
    double parallel = dwalltime() - timetick;

    printf("tiempo paralelo: %f\n", parallel);
    printf("ocurrencias: %d\n", ocurrences);

    return 0;
}
