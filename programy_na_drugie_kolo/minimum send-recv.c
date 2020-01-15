/**
 * Napisz program równoległy, który wyznacza minimum z tablicy N 
 * liczb rzeczywistych. Proces root przydziela wartości tablicy 
 * i rozsyła równe fragmenty do P procesów. Każdy z procesów (również root)
 * wyznacza minimum dla otrzymanego fragmentu. Proces root zbiera wyniki
 * częściowe i wynik wypisuje na ekranie. Do rozsyłania i zbierania
 * danych użyj funkcji: MPI_Send, MPI_Recv.
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
    float MIN_recv;

    float MIN_control = FLT_MAX;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    rest = TAB_SIZE % num_proc;

    if(rest == 0) {
        num_block = TAB_SIZE / num_proc;
    } else {
        num_block = (TAB_SIZE + num_proc - rest) / num_proc;
    }

    if(rank == 0) { // root

        // data init
        tab = malloc(TAB_SIZE * sizeof(float));
        for(i = 0; i < TAB_SIZE; i++) {
            tab[i] = i*i - 4.0 * i + 0.04;
        }

        // data send
        for(i = 1; i < num_proc; i++) {
            MPI_Send(&(tab[num_block * i]), num_block, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
        }

        // calculate own part
        for(i = 0; i < num_block; i++) {
            if(MIN > tab[i]) 
                MIN = tab[i];
        }

        // data recv
        for(i = 1; i < num_proc; i++) {
            MPI_Recv(&MIN_recv, 1, MPI_FLOAT, i, 1, MPI_COMM_WORLD, &status);
            if(MIN > MIN_recv)
                MIN = MIN_recv;
        }

        printf("MINIMUM: %.3f\n", MIN);

        // tests
        for(i = 0; i < TAB_SIZE; i++) {
            if(MIN_control > tab[i])
                MIN_control = tab[i];
        }

        // print test result
        if(MIN == MIN_control) {
            printf("Correct answer\n");
        } else {
            printf("Wrong answer\n");
        }

        free(tab);

    } else { // sleves

        // data init
        tab_recv = malloc(num_block * sizeof(float));

        // data recv
        MPI_Recv(tab_recv, num_block, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);

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

        // data send
        MPI_Send(&MIN_local, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);

        free(tab_recv);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}