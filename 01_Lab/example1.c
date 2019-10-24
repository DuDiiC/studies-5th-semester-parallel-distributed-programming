#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void* print_msg(void *ptr) {
	char *msg;
	msg = (char*)ptr;
	printf("%s\n", msg);
	return NULL;
}

int main() {

	pthread_t thread1, thread2;
	
	char *msg1="Hello";
	char *msg2="World";
	
	/* 	tworzy nowe watki na wypisanie poszczegolnych stringow */
	pthread_create(&thread1, NULL, &print_msg, (void*)msg1);
	pthread_create(&thread2, NULL, &print_msg, (void*)msg2);
	
	/* 	zapewnia, ze watek glownego programu (main) nie zostanie zakonczony,
		zanim nie zostana zakonczone watki thread1 oraz thread2 */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return EXIT_SUCCESS;
}
