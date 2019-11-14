/* Zadanie analogiczne co poprzednie (z liczeniem minumum), tylko zamiast
zmiennych lokalnych na minima, zapisujemy wszystko do zmiennej globalnej
MIN, ustawiając dostęp przy pomocy mutexow. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <float.h>

float MIN = FLT_MAX;
float CONTROL_MIN = FLT_MAX;

float* A;

int N = 2500;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct _Arg {
	int start;
	int end;
} Arg;

void* calc_min(void *ptr) {

	int i;
	Arg* arg = (Arg*)ptr;

	float local_min;
	local_min = A[arg->start];
	
	for(i = 0; i < arg->end; i++) {
		if(local_min > A[i]) {
			local_min = A[i];
		}
	}

	pthread_mutex_lock(&mutex);

	if(MIN > local_min) MIN = local_min;

	pthread_mutex_unlock(&mutex);

	return NULL;
}

void calc_control_min() {
	int i;
	for(i = 0; i < N; i++) {
		if(CONTROL_MIN > A[i]) {
			CONTROL_MIN = A[i];
		}
	}
}

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
	sleep(1); printf("Control min: %f\n", CONTROL_MIN); fflush(stdout);

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

	pthread_create(&thread1, NULL, &calc_min, (void*)_arg1);
	pthread_create(&thread2, NULL, &calc_min, (void*)_arg2);
	pthread_create(&thread3, NULL, &calc_min, (void*)_arg3);
	pthread_create(&thread4, NULL, &calc_min, (void*)_arg4);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);

	sleep(1); printf("Calculated minimum: %f\n", MIN); fflush(stdout);

	free(A);

	pthread_mutex_destroy(&mutex);

	return EXIT_SUCCESS;
}
