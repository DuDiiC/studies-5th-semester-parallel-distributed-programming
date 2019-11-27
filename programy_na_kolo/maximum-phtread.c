#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

unsigned int MIN;
unsigned int *array;
int jump = N/4;

void* calc_local_max(void *ptr) {

    int k, *m;
    unsigned int *max = malloc(sizeof(unsigned int));
    m = (unsigned int*)ptr;
    *max = array[*m];

    for(k = *m + 1; k < *m + jump; k++) {
        if(*max < array[k]) 
            *max = array[k];
    }

    printf("Local max (%ld): \t%d\n", pthread_self(), *max);

    return max;
}

int main() {

    int i;
    
    unsigned int scopes[4];
    unsigned int MAX = 0;
    void* LOCAL_MAX[4];

    pthread_t threads[4];
    
    srand((unsigned int)time((time_t*)NULL));
    array = malloc(sizeof(int)*N);

    for(i = 0; i < N; i++) {
        array[i] = rand()%100000;
    }

    for(i = 0; i < 4; i++) {
        scopes[i] = i*jump;
        pthread_create(&threads[i], NULL, &calc_local_max, (void*)&scopes[i]);
    }

    for(i = 0; i < 4; i++) {
        pthread_join(threads[i], &LOCAL_MAX[i]);
        if(*(unsigned int*)LOCAL_MAX[i] > MAX)
            MAX = *(unsigned int*)LOCAL_MAX[i];
        free(LOCAL_MAX[i]);
    }

    free(array);

    printf("Global max: \t%d\n", MAX);

    return EXIT_SUCCESS;
}