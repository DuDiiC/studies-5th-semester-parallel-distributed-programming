#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 100000000

int main() {

    int i;
    int *array = malloc(sizeof(int)*N);
    int MAX = INT_MIN;
    // int MAX_CONTROL = INT_MIN;

    srand((unsigned int)time((time_t*)NULL));

    #pragma omp parallel 
    {
        #pragma omp for reduction(max : MAX)
        for(i = 0; i < N; i++) {
            array[i] = rand()%100000;
            if(array[i] > MAX) {
                MAX = array[i];
            }
        }
    }

    // // control
    // for(i = 0; i < N; i++) {
    //     if(array[i] > MAX_CONTROL) {
    //         MAX_CONTROL = array[i];
    //     }
    // }

    // if(MAX == MAX_CONTROL) puts("OK");
    // else puts("FAILURE");

    printf("OMP: \t%d\n", MAX/*, MAX_CONTROL*/);

    return EXIT_SUCCESS;
}
