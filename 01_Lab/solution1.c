/**
 * Program ze zmienna a = 2. Proces glowny tworzy potomny (fork()), 
 * ktory zmiena a na 4, wypisuje i konczy dzialanie. 
 * Macierzysty czeka na koniec procesu potomnego (wait), 
 * wypisuje a i konczy działanie.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void fork_increase_val(int *tmp) {
	
	int child_process_id;

	/*	tworzenie procesu potomnego */
	if((child_process_id = fork()) == 0) {
		/*	proces potomny */
		(*tmp) += 2;
		printf("%d\n", *tmp);

	} else {
		/*	proces rodzica */
		wait(&child_process_id);

		printf("%d\n", *tmp);
	}
}

int main() {

	int a = 2;

	fork_increase_val(&a);

	return EXIT_SUCCESS;
}
