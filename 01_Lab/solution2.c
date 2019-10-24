#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int a = 2;

void* thread_increase(void *ptr) {
	
	a += 2;

	printf("%d\n", a);

	return NULL;
}

int main() {
	
	pthread_t thread; 

	/*	tworzenie nowego watku, wywolanie funkcji */
	pthread_create(&thread, NULL, &thread_increase, NULL);

	/*	zapewnienie, ze watek 'thread' wykona sie zanim zakonczy sie 
		glowny watek w mainie */
	pthread_join(thread, NULL);

	printf("%d\n", a);

	return EXIT_SUCCESS;
}

