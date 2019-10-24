#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void* print(void* ptr) {

	/*	alokujemy pamiec na zmienna */
	int* w = malloc(sizeof(int));
	*w = 6;
	return w;
}

int main() {
	
	pthread_t thread;
	
	void* result;
	
	pthread_create(&thread, NULL, &print, NULL);

	/* 	zapewniamy, ze watek wykona sie do konca i zapisujemy zwracana
		wartosc do wskaznika 'result' */
	pthread_join(thread, &result);
	
	/*	wypisujemy wynik, ktory najpierw trzeba zrzutowac na odpowiedni typ */
	printf("%d\n", *((int*)result));
	
	/*	zwalniamy zaalokowana na ten wynik pamiec */
	free(result);
	
	return EXIT_SUCCESS;
}
