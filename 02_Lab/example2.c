#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int data = 0;

void* my_write(void* ptr) {
	while(1) {
		/*  blokuje mozliwosc anulowania watku - jesli w glownym wywolane bedzie 
			pthread_cancel, to nie bedzie moglo zostac zrealizowane, domyslnie jest ENABLE*/
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		printf("Zabraniam\n");
		sleep(5);
		data += 1;
		printf("Pozwalam\n");

		/* 	ustawia mozliwosc anulowania watku - od teraz mozna ponownie wyslac do watku sygnal,
			ze ma zakonczyc swoje dzialanie, jednak trzeba to wymusic, jest sygnal byl wyslany wczesniej */
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

		/* 	wymusza sprawdzenie czy zostal wyslany do niego sygnal anulowania
			przez pthread_cancel (?) */
		pthread_testcancel();
	}
}

void* my_read(void* ptr) {
	while(1) {
		printf("%i\n", data);
		sleep(1);
	}
}

int main() {

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, &my_read, NULL);
	pthread_create(&thread2, NULL, &my_write, NULL);

	sleep(2);

	pthread_detach(thread1);
	pthread_detach(thread2);

	/*	odwoluje watek */
	pthread_cancel(thread2);

	pthread_exit(NULL);

	return EXIT_SUCCESS;
}
