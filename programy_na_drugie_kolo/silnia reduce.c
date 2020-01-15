#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 7

int main(int argc, char **argv) {

    int rank, num_proc, num_block, rest;
    int i;
    int factorial, local_factorial = 1;
    int start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    rest = N % num_proc;

    if(rest == 0) {
        num_block = N / num_proc;
    } else {
        num_block = (N + num_proc - rest) / num_proc;
    }

    start = rank * num_block + 1;
    end = 
        ((rank + 1) * num_block <= N) 
        ? (rank + 1) * num_block : N;

    // calculate own part
    for(i = start; i <= end; i++) {
        local_factorial *= i;
    }

    MPI_Reduce(&local_factorial, &factorial, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("%d\n", factorial);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}