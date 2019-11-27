#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define N 100

int main() {
	float A[N];
	float min, min_loc;
	int i;
	srand((unsigned int)time((time_t*)NULL));
	for(i = 0; i < N; i++) {
		A[i] = (float)rand();
		printf("%20.2f\n", A[i]);
	}
	min = A[0];
	min_loc=min;
	#pragma omp parallel firstprivate(min_loc)
	{
		#pragma omp for
		for(i = 0; i < N; i++) {
			if(A[i]<min_loc) min_loc=A[i];
		}
		#pragma omp critical
		{
			if(min_loc<min) min = min_loc;
		}
		#pragma omp barrier
		#pragma omp master
		{
			printf("%20.2f (minimum)\n", min);
		}
	}
	return EXIT_SUCCESS;
}
