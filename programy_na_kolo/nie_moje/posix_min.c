#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#define N 100000000
float A[N], MIN;
int skok = N / 4;

void *count(void* ptr){
    int k, *m;
    float *min = malloc(sizeof(float));
    m = (int *) ptr;
    *min = A[*m];
    for(k = *m+1 ; k<*m + skok ; k++){
        if(*min>A[k])
        *min = A[k];
    }
    return min;
}

int main()
{
    int i, message[4];
    pthread_t threads[4];
    void *wynik;

    for(i = 0; i<4 ; i++)
        message[i] = i*skok;
    srand(time(NULL));

    for(i = 0; i<N ; i++){
        A[i] = (float)(rand()%100)+1;
        //printf("%20.2f\n",A[i]);
    }
    MIN = A[0];

    for(i = 0; i<4 ; i++)
        pthread_create(&threads[i], NULL, &count, (void*)&message[i]);

    for(i = 0; i<4 ; i++){
        pthread_join(threads[i],&wynik);
        if(*(float*)wynik < MIN)
            MIN = (*(float*)wynik);

        free(wynik);
    }
    printf("\nMIN:%15.2f\n",MIN);
    return EXIT_SUCCESS;
}