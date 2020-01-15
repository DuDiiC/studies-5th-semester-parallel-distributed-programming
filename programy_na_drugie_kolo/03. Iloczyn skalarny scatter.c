#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 100

int main(int argc,char **argv){

	float *A, *B, *Arev, *Brev, c = 0, d;
	int rank, i, p, r, q;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	r=N%(p);
    if(r==0)q=N/p;
    else q=(N+p-r)/(p);

	Arev=malloc(q*sizeof(float));
	Brev=malloc(q*sizeof(float));

	if(rank==0){ //alokujemy pamiec i inicjalizujemy dane
		A=calloc(q*p,sizeof(float));
		B=calloc(q*p,sizeof(float));
		for(i=0;i<N;i++){
			A[i]=i;
			B[i]=2;
		}
	}

	// wyslanie danych z jednego procesu do wszystkich innych procesow w komunikatorze .Podajemy:
	// bufor do wyslania, rozmiar bufora, typ danych, bufor odbierajacy, rozmiar bufora, typ danych, numer procesu wysylajacego, komunikator
	// te dwie funkcje zamiast wysylania w petli do kazdego procesu z osobna
	MPI_Scatter(A, q, MPI_FLOAT, Arev, q, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, q, MPI_FLOAT, Brev, q, MPI_FLOAT, 0, MPI_COMM_WORLD);

	for(i=0;i<q;i++) c+=Arev[i]*Brev[i]; // ta czesc jest wykonywana przez wszystkie procesy...?

	if(rank==0) { // jesli proces macierzysty

		for(i=1;i<p;i++){ // od kazdego procesu odbieramy dane i dodajemy do bufora
			MPI_Recv(&d,1,MPI_FLOAT,i,1,MPI_COMM_WORLD,&status);
			c+=d;
		}

		// wypisujemy wynik i zwalniamy pamiec
		printf("%f\n",c);
		free(A);
		free(B);

	} else { 

		MPI_Send(&c,1,MPI_FLOAT,0,1,MPI_COMM_WORLD); // odeslanie do procesu macierzystego wyniku z linii 39
	}

	free(Arev);
	free(Brev);

	MPI_Finalize();
	return EXIT_SUCCESS;
}

