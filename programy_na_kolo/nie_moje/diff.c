#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define N 12

int main(){
    int i,j;
    float A[N], max_loc, max,diff;
    srand(time(NULL));
        for(i=0;i<N;i++){
            A[i] = (float)(rand()%100)+1;
            printf("%20.2f\n",A[i]);
        }
        max = fabs(A[0]-A[1]);
        max_loc = max;
#pragma omp parallel default(shared) private(i , j ,max_loc, diff)
{
    #pragma omp for schedule(static)
        for(i = 1 ; i < N; i++)
                for(j = i+1; j<N; j++){
                    diff = fabs(A[i]-A[j]);
                    if(diff>max_loc)
                        max_loc = diff;
                }
    #pragma omp critical
    {
        if(max_loc>max)
            max = max_loc;
    }
    #pragma omp barrier
    #pragma omp master
    {
        printf("\nMax diff:%20.2f\n",max);
    }
}
return EXIT_SUCCESS;
}