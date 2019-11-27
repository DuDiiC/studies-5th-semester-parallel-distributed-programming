#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int i, tid;
	/* zrownoleglenie fragmentu w bloku po dyrektywie */
	
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		sleep(2);
		printf("to ja z numerem: %d\n", tid);
		#pragma omp critical
		{
			sleep(2);
			printf("sekcja: critical, to ja numer: %d\n", tid);
		}
		#pragma omp barrier
		#pragma omp master
		{
			sleep(2);
			printf("sekcja: master, to ja numer: %d\n", tid);
		}
		printf("KONIEC %d\n", tid);
	}

	return EXIT_SUCCESS;
}
