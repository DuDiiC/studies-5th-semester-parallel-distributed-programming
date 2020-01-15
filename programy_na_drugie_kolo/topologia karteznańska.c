/**
 * Napisz program, który tworzy komunikator z topologią kartezjańską (zdj)
 * Wyznacz za pomocą funkcji MPI_Cart_shift i wypisz na ekranie sasiadów każdego
 * wierzchołka grafu.
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	
	int rank, neighbors[4], coords[2],
	
	ndims = 2,
	dims[2] = { 2, 3 },
	periods[2] = { 1, 0 };
	
	MPI_Comm comm_cart;

	MPI_Init(&argc, &argv);
	MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, 0, &comm_cart);
	MPI_Comm_rank(comm_cart, &rank);
	
	MPI_Cart_coords(comm_cart, rank, 2, coords);
	
	MPI_Cart_shift(comm_cart, 0, 1, &neighbors[0], &neighbors[1]);
	MPI_Cart_shift(comm_cart, 1, 1, &neighbors[2], &neighbors[3]);
	
	printf("rank= %d wpolrzedne= %d %d  sasiedzi= %d %d %d %d\n", 
			rank, coords[0], coords[1], neighbors[0], neighbors[1], neighbors[2], neighbors[3]);
	
	MPI_Finalize();
	return EXIT_SUCCESS;
}
