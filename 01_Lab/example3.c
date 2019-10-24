#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*	zmienna globalna, ktora bedziemy modyfikowac */
int a = 2;

/* struktura, ktora bedziemy przekazywac do funkcji watku */
typedef struct _Arg {
	int b;
	int c;
} Arg;

void* print_msg(void* arg) {
	
	Arg *local_arg = (Arg*)arg;

	a = a+local_arg->b;
	a = a*local_arg->c;
	printf("%d\n", a);
	return NULL;
}

int main() {

	Arg arg = {3, 2};
	pthread_t thread;
	pthread_create(&thread, NULL, &print_msg, (void*)&arg);
	pthread_join(thread, NULL);
	printf("%d\n", a);

	return EXIT_SUCCESS;
}
