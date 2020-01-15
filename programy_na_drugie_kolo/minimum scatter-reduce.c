/**
 * Napisz program równoległy, który wyznacza minimum z tablicy N 
 * liczb rzeczywistych. Proces root przydziela wartości tablicy 
 * i rozsyła równe fragmenty do P procesów. Każdy z procesów (również root)
 * wyznacza minimum dla otrzymanego fragmentu. Proces root zbiera wyniki
 * częściowe i wynik wypisuje na ekranie. Do rozsyłania i zbierania
 * danych użyj funkcji: MPI_Scatter, MPI_Reduce.
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <mpi.h>

#define TAB_SIZE 20

int main(int argc, char **argv) {

    int rank, num_proc, num_block, rest;
    int i;
    float* tab;
    float* tab_recv; 
    float MIN = FLT_MAX;
    float MIN_local = FLT_MAX;

    float MIN_control = FLT_MAX;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    rest = TAB_SIZE % num_proc;

    if(rest == 0) {
        num_block = TAB_SIZE / num_proc;
    } else {
        num_block = (TAB_SIZE + num_proc - rest) / num_proc;
    }

    tab = malloc(TAB_SIZE * sizeof(float));
    tab_recv = malloc(num_block * sizeof(float));
    if(rank == 0) { // root

        // data init
        for(i = 0; i < TAB_SIZE; i++) {
            tab[i] = i*i - 4.0 * i + 0.04;
        }
    }
        
    // send data
    MPI_Scatter(tab, num_block, MPI_FLOAT, tab_recv, num_block, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(rank == num_proc - 1) { // last slave has less elements
        // caclucate own part
        for(i = 0; i < num_block - rest; i++) {
            if(MIN_local > tab_recv[i]) 
                MIN_local = tab_recv[i];
        }
    } else {
        // caclucate own part
        for(i = 0; i < num_block; i++) {
            if(MIN_local > tab_recv[i]) 
                MIN_local = tab_recv[i];
        }
    }

    // reduce minimum
    MPI_Reduce(&MIN_local, &MIN, 1, MPI_FLOAT, MPI_MIN, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("MINIMUM: %f\n", MIN);
    }

    free(tab);
    free(tab_recv);

    MPI_Finalize();
    return EXIT_SUCCESS;
}