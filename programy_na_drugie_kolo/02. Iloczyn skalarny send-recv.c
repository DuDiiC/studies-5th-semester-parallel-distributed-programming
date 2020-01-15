/* iloczyn skalarny dwoch wektorow 
A - wektor pierwszy
B - wektor drugi
Arev - wysłany wektor pierwszy
Brev - wysłany wektor drugi 
rank - identyfikator procesu (jak 0 to wysyłamy, jak inny to odbieramy) 
p - liczba procesow
c - wynik iloczynu
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 100

int main(int argc,char **argv) {
	
	float *A, *B, *Arev, *Brev, c = 0, d;
	int rank, i, p, r, q;

	// inicjalizacja mechanizmu MPI
	MPI_Status status;
	MPI_Init(&argc,&argv);
	// pobranie numeru procesu
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	// pobranie liczby procesow
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	
	// sprawdzenie reszty z dzielenia rozmiaru wektora przez liczbe procesow...?
	r = N%p;
	// nie mam pojecia co robi q
	if(r == 0) {
		q = N/p;
	} else {
		q = (N + p - r)/p;
	}

	if(rank == 0) { // jesli to pierwszy proces
		
		// alokujemy pamiec na wektory
		A = calloc(q * p, sizeof(float));
		B = calloc(q * p, sizeof(float));
		
		// inicjalizujemy je
		for(i = 0; i < N; i++) {
			A[i] = i;
			B[i] = 2;
		}

		// wysylamy porcje danych FLOAT o rozmiarze q do i-tego procesu. Wiadomość ma identyfikator 1
		for(i = 1; i < p; i++) {
			MPI_Send(&(A[i*q]), q, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
			MPI_Send(&(B[i*q]), q, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
		}

		//  liczenie pierwszej partii danych
		for(i=0;i<q;i++) {
			c += A[i] * B[i];
		}

		// odebranie porcji danych i dodanie obliczonego wyniku do sumy
		for(i = 1; i < p; i++) {
			MPI_Recv(&d, 1, MPI_FLOAT, i, 1, MPI_COMM_WORLD, &status);
			c += d;
		}

		// wypisanie wyniku i zwolnienie pamieci dla wektorow
		printf("%f\n",c);
		free(A);	
		free(B);

	} else {
		
		// alokacja pamieci dla wektorow wyslanych
		Arev = malloc(q * sizeof(float));
		Brev = malloc(q * sizeof(float));
		
		// odbior porcji danych FLOAT od procesu 0 z id 1
		MPI_Recv(Arev, q, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(Brev, q, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
		
		// wykonanie swojej czesci obliczen
		for(i = 0; i < q; i++) {
			c += Arev[i] * Brev[i];
		}

		// odeslanie wyniku do procesu 0
		MPI_Send(&c, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
		
		// zwolnienie pamieci
		free(Arev);
		free(Brev);
	}

	// zakonczenie mechanizmu MPI
	MPI_Finalize();
	return EXIT_SUCCESS;	
}
