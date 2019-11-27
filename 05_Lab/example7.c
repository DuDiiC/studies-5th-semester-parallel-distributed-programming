#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int i, tid;
	omp_set_num_threads(2); /* zmiana liczby watkow */
	/* zrownoleglenie fragmentu w bloku po dyrektywie */
	# pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		/* zrownoleglenie petli po dyrektywie */
		# pragma omp for nowait
		for(i = 0; i < 8; i++) {
			sleep(tid);
			printf("to ja z numerem: %d, robie i = %d\n", tid, i);
		}
		printf("KONIEC %d\n", tid);
	}

	return EXIT_SUCCESS;
}
