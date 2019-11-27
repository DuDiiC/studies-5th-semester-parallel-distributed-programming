/* Dane dwie tablice a[N], b[N]. Napisz program wspolbiezny, 
ktory wyznaczy iloczyn skalarny tych tablic. */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

int a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
int aPrim[N] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int b[N] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int bPrim[N] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

int global_dot = 0;

int main() {
	int i, tid, tmp = 0;
	
	#pragma omp parallel private(tid) firstprivate(tmp)
	{
		tid = omp_get_thread_num();
		printf("to ja z numerem: %d\n", tid);

		#pragma omp for schedule(dynamic, 1)
		for(i = 0; i < N; i++) {
			tmp += a[i] * b[i];
		}
		#pragma omp critical
		{
			global_dot += tmp;
		}
	}
	
	printf("Iloczyn skalarny: %d\n", global_dot);

	return EXIT_SUCCESS;
}
