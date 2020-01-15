#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 100

int main(int argc,char **argv) {

	float *A, *B, *C, *Arev, *Brev, c = 0;
	int rank, i, p, r, q;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	r = N%(p);
    if(r==0)q=N/p;  
    else q=(N+p-r)/(p); 	

	// alokacja pamieci dla tablic z danymi rozeslanych fragmentow wektorow
	Arev = malloc(q * sizeof(float));
	Brev = malloc(q * sizeof(float));

	if(rank == 0) { // inicjalizacja w procesie macierzystym
		A = calloc(q * p, sizeof(float));
		B = calloc(q * p, sizeof(float));
		C = malloc(p * sizeof(float));
		for(i = 0; i < N; i++) {
			A[i] = i;
			B[i] = 2;
		}
	}

	// rozeslanie do wszystkich procesow odpowiednich fragmentow tablicy
	MPI_Scatter(A, q, MPI_FLOAT, Arev, q, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, q, MPI_FLOAT, Brev, q, MPI_FLOAT, 0, MPI_COMM_WORLD);

	for(i=0;i<q;i++) c+=Arev[i]*Brev[i]; // obliczenia w kazdym z procesow...?

	// pobranie tablicy wynikow ze wszystkich procesow do procesu macierzystego
	MPI_Gather(&c, 1, MPI_FLOAT, C, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		// zsumowanie wszystkich wynikow czastkowych z poszczegolnych obliczen linii 37 na kazdym z procesow
		for(i = 1; i < p; i++) c += C[i];

		printf("%f\n",c);
		free(A);
		free(B);
		free(C);
	}

	// zwolnienie pamieci i zakonczenie mechanizmu MPI
	free(Arev);
	free(Brev);
	MPI_Finalize();
	return EXIT_SUCCESS;
}
