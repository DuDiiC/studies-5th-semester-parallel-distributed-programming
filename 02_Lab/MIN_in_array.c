/* Dana jest tablica globalna float A[N] i zmienna globalna float MIN, 
gdzie N jest liczba naturalna podzielna przez 4.
Napisz program, ktory wyznacza minimum z powyzszej tablicy (wynik w MIN) przez 4 watki. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <float.h>

#define N 2500

typedef struct _Arg {
	int start;
	int end;
} Arg;

float MIN = FLT_MAX;
float CONTROL_MIN = FLT_MAX;
int position;

float* A;

void* calc_min(void *ptr);

void calc_control_min();	

int main() {

	int i;
	
	/* create array with float numbers */
	A = malloc(sizeof(float) * N);

	srand(time(NULL));
	for(i = 0; i < N; i++) {
		A[i] = rand() / (float) RAND_MAX + rand();
	}

	/*	test in one thread */
	calc_control_min();
	
	printf("One-threaded method"); fflush(stdout); 
	sleep(1); printf("."); fflush(stdout);
	sleep(1); printf("."); fflush(stdout);
	sleep(1); printf(".\n"); fflush(stdout);
	sleep(1); printf("Control min: %f on position %d\n", CONTROL_MIN, position); fflush(stdout);

	/* multithreaded */
	pthread_t thread1, thread2, thread3, thread4;
	
	Arg arg1 = {0, N/4 - 1},
		arg2 = {N/4, N/2 - 1},
		arg3 = {N/2, N/4 + N/2 - 1},
		arg4 = {N/4 + N/2, N - 1};

	Arg *_arg1 = &arg1;
	Arg *_arg2 = &arg2;
	Arg *_arg3 = &arg3;
	Arg *_arg4 = &arg4;

	float *min1, *min2, *min3, *min4;

	pthread_create(&thread1, NULL, &calc_min, (void*)_arg1);
	pthread_create(&thread2, NULL, &calc_min, (void*)_arg2);
	pthread_create(&thread3, NULL, &calc_min, (void*)_arg3);
	pthread_create(&thread4, NULL, &calc_min, (void*)_arg4);

	pthread_join(thread1, (void*)&min1);
	pthread_join(thread2, (void*)&min2);
	pthread_join(thread3, (void*)&min3);
	pthread_join(thread4, (void*)&min4);

	sleep(1); printf("Multi-treaded method...\n"); fflush(stdout);
	sleep(1); printf("1st: %f\n", *min1); fflush(stdout); 
	sleep(1); printf("2nd: %f\n", *min2); fflush(stdout);
	sleep(1); printf("3td: %f\n", *min3); fflush(stdout);
	sleep(1); printf("4th: %f\n", *min4); fflush(stdout);

	MIN = *min1;
	if(MIN > *min2) MIN = *min2;
	if(MIN > *min3) MIN = *min3;
	if(MIN > *min4) MIN = *min4;

	sleep(1); printf("Calculated minimum: %f\n", MIN);

	free(A); free(min1); free(min2); free(min3); free(min4);

	return EXIT_SUCCESS;
}

void* calc_min(void *ptr) {

	int i;
	Arg* arg = (Arg*)ptr;

	float *local_min = malloc(sizeof(float));
	*local_min = A[arg->start];
	
	for(i = 0; i < arg->end; i++) {
		if(*local_min > A[i]) {
			*local_min = A[i];
		}
	}

	return local_min;
}

void calc_control_min() {
	int i;
	for(i = 0; i < N; i++) {
		if(CONTROL_MIN > A[i]) {
			CONTROL_MIN = A[i];
			position = i;
		}
	}
}