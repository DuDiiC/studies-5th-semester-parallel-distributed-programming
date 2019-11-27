#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 10
int main() {
    float A[N];
    float min, min_loc;
    int i;
    srand((unsigned int)time((time_t *)NULL));
    for (i = 0; i < N; i++) {
        A[i] = (float)(rand()%100)+1;
        printf("%20.2f\n", A[i]);
    }
    min = A[0];
    min_loc = min;
    #pragma omp parallel firstprivate(min_loc)
    {
        #pragma omp for
        for (i = 0; i < N; i++) {
            if (A[i] < min_loc)
            min_loc = A[i];
        }
    #pragma omp critical
    {
      if (min_loc < min)
        min = min_loc;
    }
#pragma omp barrier
#pragma omp master
    { printf(" MIN : %20.2f\n", min); }
  }
  return EXIT_SUCCESS;
}