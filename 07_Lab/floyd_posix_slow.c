#define _POSIX_C_SOURCE 200809L
#include<pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define N 8
#define NUM_THREADS 4
#define MIN(a,b) (((a)<(b))?(a):(b))
int step=N/NUM_THREADS;
int I[N][N];
int J[N][N];
pthread_barrier_t	bariera;

void* count(void* ptr){
	int i,j,k;
	int local_i_start=*((int*)ptr);
	int local_i_end=*((int*)ptr)+step;
	for(k=0;k<N;k++){
		for(i=local_i_start;i<local_i_end;i++) 
			for(j=0;j<N;j++)J[i][j]=MIN(I[i][j],I[i][k]+I[k][j]); 
		pthread_barrier_wait(&bariera);
		for(i=local_i_start;i<local_i_end;i++) 
			memcpy(&(I[i][0]),&(J[i][0]),N*sizeof(int));
		pthread_barrier_wait(&bariera);
	}
	return NULL;
}
int main(){
	int i,j;
	int arg[NUM_THREADS];
	pthread_t thread[NUM_THREADS];
	srand((unsigned int)time((time_t*)NULL));
	for(i=0;i<N;i++)for(j=0;j<N;j++){
		if(i==j){I[i][j]=0;continue;}
		I[i][j]=(rand()/100000000);
		if(I[i][j]>9)I[i][j]=1000000;
	};
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)printf("\t%d",I[i][j]);
		printf("\n");
	}
	printf("\n");
	pthread_barrier_init(&bariera, NULL, NUM_THREADS);
	for(i=0;i<NUM_THREADS;i++){
		arg[i]=i*step;
		pthread_create(&thread[i],NULL,&count,&arg[i]);
	}
	for(i=0;i<NUM_THREADS;i++)pthread_join(thread[i],NULL);

	for(i=0;i<N;i++){
		for(j=0;j<N;j++)printf("\t%d",I[i][j]);
		printf("\n");
	}
	pthread_barrier_destroy(&bariera);
	return EXIT_SUCCESS;
}

