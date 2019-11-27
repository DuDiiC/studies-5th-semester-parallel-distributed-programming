#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int i, tid;
# pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
# pragma omp for schedule(dynamic,1)
		for(i = 0; i < 8; i++) {
			sleep(tid);
			printf("to ja z numerem: %d, robie i = %d\n", tid, i);
		}
	}

	return EXIT_SUCCESS;
}
