#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 8

/* program watkowo liczy iloczyn macierzy */

int main() {

	int   i,j,k;
	float A[N][N], B[N][N], C[N][N];

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
  			A[i][j] = i;
			B[i][j] = 2;
			C[i][j] = 0;
		}
		# pragma omp parallel for reduction(+: j,k) reduction(*: j,k)
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				for(k = 0; k < N; k++) {
					C[i][j] += A[i][k]*B[k][j];
				}
			}
		}
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%f,",C[i][j]);
		}
		printf("\n");
	}

	return EXIT_SUCCESS;
}
