#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

	int i;
	int n, result = 1;

	scanf("%d", &n);

	#pragma omp parallel reduction(*:result)
	{
		printf("%d\n", omp_get_num_threads());
		# pragma omp for
		for (i = 2; i <= n; i++) {
			result *= i;
		}
	}

	printf("%d\n", result);

	return EXIT_SUCCESS;
}
