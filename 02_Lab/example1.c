/**
 * Program pokazuje jak dzialaja odlaczone watki.
 * Jeden z nich pisze do pliku, drugi wypisuje wartosc.
 */	

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int data = 0;

void* my_write(void* ptr) {
	while(1) {
		data+=1;
		sleep(2);
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

	/* odlaczenie watkow - glowny nie czeka na zakonczenie thread1 i thread2 */
	pthread_detach(thread1);
	pthread_detach(thread2);

	printf("Watek glowny...\n");

	/* konczy watek glowny */
	pthread_exit(NULL);

	return EXIT_SUCCESS;
}
