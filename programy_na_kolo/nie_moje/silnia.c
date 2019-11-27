#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 6

int main(){
    int i, fac = 1;

#pragma omp parallel
{
    #pragma omp for reduction(*:fac)
        for(i=2;i<=N;++i)
        {
            fac *=i;
        }
}
printf("Silnia: %d! = %d\n",N,fac);
return EXIT_SUCCESS;
}