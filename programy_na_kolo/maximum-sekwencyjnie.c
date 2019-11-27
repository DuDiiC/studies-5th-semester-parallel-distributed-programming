#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

int main() {

    int i; 
    unsigned int MAX = 0; 

    unsigned int *tmp = malloc(sizeof(unsigned int));

    srand((unsigned int)time((time_t*)NULL));

    for(i = 0; i < N; i++) {
        *tmp = rand()%100000;
        if(*tmp > MAX) 
            MAX = *tmp;
    }

    free(tmp);

    printf("%d\n", MAX);

    return EXIT_SUCCESS;
}