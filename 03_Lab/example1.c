/* 	Program pokazuje proste dzialanie mutexow, aby watki nie
	probowaly jednoczesnie czytac/pisac z tego samego zasobu.
	Dzialanie mutexow jest analogiczne do dzialania semaforow,
	czy slowa kluczowego `synchronized` w Javie. */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int data = 0;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* my_write(void* ptr) {
	while(1) {
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		/* mutex blokuje wykonywanie tego bloku wielowatkowo */
		pthread_mutex_lock(&mutex1);
		data += 1;
		sleep(1);
		/* mutex odblokowuje wykonywanie tego bloku wielowatkowo */
		pthread_mutex_unlock(&mutex2);
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		pthread_testcancel();
	};
}

void* my_read(void* ptr){
	while(1) {
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		/* analogicznie */
		pthread_mutex_lock(&mutex2);
		printf("%i\n", data);
		sleep(3);
		/* analogicznie */
		pthread_mutex_unlock(&mutex1);
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		pthread_testcancel();
	};
}	

int main(){

	pthread_t thread1,thread2;
	int signum;
	sigset_t mask;
	
	/* wstepne ustawienie obslugi sygnaly ctrl+c */
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	pthread_sigmask(SIG_BLOCK, &mask, NULL);

	/* zablokowanie mutexu drugiego, odblokowany jest pierwszy */
	pthread_mutex_lock(&mutex2);
	
	pthread_create(&thread1,NULL,&my_read,NULL);
	pthread_create(&thread2,NULL,&my_write,NULL);

	/* main czeka na otrzymanie sygnalu `mask` i zwraca wynik do zmiennej `signum` */
	sigwait(&mask, &signum);

	/* teraz 'sprzatamy, tzn. konczymy watki, niszczymy mutexy */
	pthread_cancel(thread1);	
	pthread_cancel(thread2);	
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	pthread_mutex_destroy(&mutex1);	
	pthread_mutex_destroy(&mutex2);	
	
	return EXIT_SUCCESS;	
}
