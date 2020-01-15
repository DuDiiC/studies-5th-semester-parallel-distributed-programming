/**
 * Napisz program, którzy tworzy komunikator z topologią grafową postaci:
 * (0) --- (2)
 * (0) --- (3)
 * (1) --- (2)
 * Wyznacz za pomocą funkcji MPI_Graphneighbors i wypisz na ekranie sąsiadów,
 * każdego wierzchołka grafu.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, int **argv) {

    int rank, count;
    int i;
    int *neighbors;
    int nnodes = 4,
        index[4] = {2, 3, 5, 6},
        edges[6] = {2, 3, 2, 0, 1, 0};
    
    MPI_Comm comm_graph;
    MPI_Init(&argc, &argv);

    MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, i, &comm_graph);

    MPI_Comm_rank(comm_graph, &rank);

    MPI_Graph_neighbors_count(comm_graph, rank, &count);

    neighbors = malloc(count * sizeof(int));

    MPI_Graph_neighbors(comm_graph, rank, count, heighbors);

    printf("For index: %d\n", rank);
    for(i = 0; i < count; i++) {
        printf("%d ", neighbors[i]);
    }
    printf("\n");

    free(neighbors);
    MPI_Finalize();

    return EXIT_SUCCESS;
}