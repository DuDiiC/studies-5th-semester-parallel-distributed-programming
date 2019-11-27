#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int tid;
	# pragma omp parallel
	{
		tid = omp_get_thread_num();
		sleep(1);
		printf("to ja z numerem: %d\n", tid);
	}

	return EXIT_SUCCESS;
}
