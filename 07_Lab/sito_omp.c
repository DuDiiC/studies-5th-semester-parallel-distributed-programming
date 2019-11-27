#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>
#include <omp.h>

int main(int argc, char * argv[]){
	int N = 100;
	int sqrtN = 4;
	int c = 2;
	int m = 3;
	int *list;
	char next_option=' ';
	while((next_option = getopt(argc, argv, "n:")) != -1) {
		switch(next_option) {
			case 'n':
				N = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-n N]\n", argv[0]);
				exit(-1);
		}
	}
	sqrtN = (int)sqrt(N);
	list = (int*)malloc(N * sizeof(int));
	if(list == NULL) {
		fprintf(stderr, "Error: Failed to allocate memory for list.\n");
		exit(-1);
	}
	# pragma omp parallel
	{
	# pragma omp for
	for(c = 2; c <= N-1; c++) {
		list[c] = 0;
	}
	for(c = 2; c <= sqrtN; c++) {
		if(list[c] == 0) {
			# pragma omp for
			for(m = c+1; m <= N-1; m++) {
				if(m%c == 0) {
					list[m] = 1;
				}
			}
		}
	}
	}
	//for(c = 2; c <= N-1; c++) {
	//	if(list[c] == 0) {
	//		printf("%d ", c);
	//	}
	//}
	//printf("\n");
	free(list);
	return EXIT_SUCCESS;
}
