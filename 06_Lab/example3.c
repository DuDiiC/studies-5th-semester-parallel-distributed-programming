#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100

int main() {
	
	int i;
	float a[N], b[N], iloczyn = 0;

	for(i = 0; i < N; i++) {
		a[i] = i;
		b[i] = 2;
	}

	# pragma omp parallel
	{
		# pragma omp for reduction(+:iloczyn)
		for(i = 0; i < N; i++) {
			iloczyn += (a[i] * b[i]);
		}
	}

	printf("iloczyn skalarny: %f\n", iloczyn);

	return EXIT_SUCCESS;
}
