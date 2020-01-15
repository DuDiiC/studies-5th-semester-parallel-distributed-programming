#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc,char **argv) {
	
	int my_rank;
	char *message;

	MPI_Status status;
	
	MPI_Init(&argc, &argv); /* inicjuje mechanizm MPI */
	/* Zwraca do zmiennej my_rank identyfikator procesu, ktory wywoluje te funkcje. Sa tu liczby z zakresu (0, size-1), gdzie size to liczba dostepnych procesow. */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	if(my_rank == 0) { // jesli jestesmy w pierwszym procesie chcemy wyslac wiadomosc

		message = malloc(6);
		strncpy(message, "Hello", 6);
		MPI_Send(message, 6, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
		strncpy(message, "World", 6);
		MPI_Send(message, 6, MPI_CHAR, 2, 1, MPI_COMM_WORLD);
		free(message);

	} else { // jesli nie jestesmy w pierwszym procesie chcemy odebrac wiadomosc
		
		message = malloc(6);
		MPI_Recv(message, 6, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
		printf("%s\n", message);
		free(message);
	}

	MPI_Finalize(); /* konczy prace w trybie MPI */
	return EXIT_SUCCESS;
}
