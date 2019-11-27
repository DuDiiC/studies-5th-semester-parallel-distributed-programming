/* Dana jest tablica A[N]. Wyznacz minimum z tablicy A. */

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define N 100

int A[N];
int MIN_SEKW = INT_MAX;
int MIN_CRITICAL = INT_MAX;
int MIN_REDUKCJA = INT_MAX;
int MIN_WATKU = INT_MAX;

int main() {

	int i, j;

	srand(time(NULL));

	for(i = 0; i < N; i++) {
		A[i] = rand();
	}

	/* sekwencyjnie, dla sprawdzenia */
	for(i = 0; i < N; i++) {
		if(A[i] < MIN_SEKW) {
			MIN_SEKW = A[i];
		}	
	}
	
	/* przy uzyciu critical */
	# pragma omp parallel firstprivate(MIN_WATKU)
	{
		# pragma omp for
		for(i = 0; i < N; i++) {
			if(A[i] < MIN_WATKU) {
				MIN_WATKU = A[i];
			}	
		}

		# pragma omp critical
		{
			if(MIN_WATKU < MIN_CRITICAL) {
				MIN_CRITICAL = MIN_WATKU;
			}
		}	
	}

	/* przy uzyciu redukcji */
	# pragma omp parallel reduction(min: MIN_REDUKCJA)
	{
		# pragma omp for
		for(i = 0; i < N; i++) {
			if(A[i] < MIN_REDUKCJA) {
				MIN_REDUKCJA = A[i];
			}
		}
	}


	printf("sekwencyjne: \t\t%d\nomp for: \t\t%d\nredukcja: \t\t%d\n", 
			MIN_SEKW, MIN_CRITICAL, MIN_REDUKCJA);

	return EXIT_SUCCESS;
}
