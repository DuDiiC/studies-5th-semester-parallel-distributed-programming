/* 	program z uzyciem algorytmu Floyda
	dzialajacy wspolbieznie, przy uzyciu bariery */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define N 128
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

int I[N][N];
int J[N][N];

pthread_barrier_t barrier;

void *calc_selected_matrix(void *arg) {
	int k, j;
	int i = *(int*)arg;

	for(k = 0; k < N; k++) {
		for(j = 0; j < N; j++) {
			J[i][j] = MIN(I[i][j], I[i][k] + I[k][j]);
		}
		memcpy(&(I[i][0]), &(J[i][0]), N*sizeof(int));
		pthread_barrier_wait(&barrier);
	}
}

int main() {

	int i,j,k;
	pthread_t thread[N];

	srand((unsigned int)time((time_t*)NULL));

	for(i = 0; i < N; i++) {
		for(j=0;j<N;j++) {
			
			if(i == j) { 
				I[i][j] = 0;
				continue;
			}
		
			I[i][j] = (rand()/100000000);
			
			if(I[i][j] > 9) {
				I[i][j]=1000000;
			}
		}
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("\t%d", I[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	
	pthread_barrier_init(&barrier, NULL, N);

	for(i = 0; i < N; i++) {
		pthread_create(&thread[i], NULL, &calc_selected_matrix, (void*)&i);
	}

	for(i = 0; i < N; i++) {
		pthread_join(thread[i], NULL);
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("\t%d", I[i][j]);
		}
		printf("\n");
	}

	return EXIT_SUCCESS;
}
