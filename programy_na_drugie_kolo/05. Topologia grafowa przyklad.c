/*
 * utworzyc komunikator z topologia grafowa
 * [0]---[1]
 * [0]---[2]
 * [0]---[3]
 * [1]---[3]
 * [3]---[4]
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {

	int rank,i,count;
	int* neighbors;
	int nnodes=5,
		index[5] = {3,5,6,9,10}, // kazdy kolejny index ma liczbe krawedzi = nr - nr_poprzedniego
		edges[10] = {1,2,3,0,3,0,0,1,4,3}; // podajemy z jakimi numerami indeksow jest krawedz
	
	MPI_Comm comm_graph;
	MPI_Init(&argc,&argv);
	// inicjujemy komunikator grafu z:
	// piecioma wierzcholkami, 
	// tablica index dajaca informacje ile krawedzi ma wierzcholek
	// tablica edges dajaca informacje do ktorych wierzcholkow prowadza krawedzie 
	MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, 1, &comm_graph);
	
	// pobieramy numer procesu w topologii grafowej czyli nr wierzcholka
	MPI_Comm_rank(comm_graph, &rank);
	
	// zwraca dla kazdego wierzcholka liczbe sasiadow
	MPI_Graph_neighbors_count(comm_graph, rank, &count);
	
	neighbors = malloc(count * sizeof(int));
	
	// wpisuje do tablicy neighbors dane na temat sasiadow wierzcholka o podanym numerze
	MPI_Graph_neighbors(comm_graph, rank, count, neighbors);
	
	// wypisujemy wszystkich sasiadow dla kazdego wierzcholka
	for(i = 0; i < count; i++)
		printf("(%d)----(%d)\n", rank, neighbors[i]);
	
	free(neighbors);
	MPI_Finalize();
	return EXIT_SUCCESS;
}
