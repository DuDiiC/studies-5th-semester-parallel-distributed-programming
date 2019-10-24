#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void fork_increase_val(int *tmp) {
	
	int status;

	/*	tworzenie procesu potomnego */
	if(fork() == 0) {
		/*	proces potomny */
		(*tmp)+=2;
		printf("%d\n", *tmp);

	} else {
		/*	proces rodzica */
		wait(&status);

		printf("%d\n", *tmp);
	}

}

int main() {

	int a = 2;

	fork_increase_val(&a);

	return EXIT_SUCCESS;
}
