#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils.c"

int T, N;
int *array;


void merge(int *arr, int left, int mid, int right){
    int i, j, k;    

    int left_size = mid - left + 1;
    int right_size = right - mid;

    int left_arr[left_size], right_arr[right_size];

    //copy the arrays
    for (i = 0; i < left_size; i++){
        left_arr[i] = arr[left + i];
    }
    for (j = 0; j < right_size; j++){
        right_arr[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < left_size && j < right_size){
        if (left_arr[i] <= right_arr[j]){
            arr[k] = left_arr[i];
            i++;
        }
        else{
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    //copy the remaining elements
    while (i < left_size){
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    while (j < right_size){
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int *arr, int left, int right){
    if (left >= right) return;

    int mid = left + (right-left)/2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

void copy_array(int *arr1, int *arr2, int size){
    for (int i = 0; i < size; i++) arr2[i] = arr1[i];
}

void *func(void *arg){
    int id = *(int*)arg;

    int left = id * (N/T);
    int right = (id + 1) * (N/T) - 1;

    merge_sort(array, left, right);

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

    array = (int*)malloc(sizeof(int)*N);
    random_arr(array, N);
    int *arr2 = (int*)malloc(sizeof(int)*N);
    copy_array(array, arr2, N);

    //procesamiento secuencial
    double timetick = dwalltime();
    merge_sort(arr2, 0, N-1);

    double seq = dwalltime() - timetick;

    printf("tiempo secuencial: %f\n", seq);
    
    // procesamiento paralelo
    timetick = dwalltime();
    init_threads(threads, threadsIDs, T);

    wait_threads(threads, T);

    //???
    int step = N / T;
    for (int size = step; size < N; size *= 2) {
        for (int left = 0; left < N - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < N) ? (left + 2 * size - 1) : (N - 1);
            merge(array, left, mid, right);
        }
    }

    double parallel = dwalltime() - timetick;

    printf("tiempo paralelo: %f\n", parallel);

    free(array);
    free(arr2);

    return 0;
}

