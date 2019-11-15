/* 	Program pokazuje w jaki sposob mozna ustawic mutexy, aby
	czekaly na odpowiedni warunek przy uzyciu zmiennej pthread_cond_t */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int a=0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* write_this(void* ptr) {
	
	pthread_mutex_lock(&mutex);
	printf("watek drugi: zajalem zasob\n");
	
	if(a!=5) {
		printf("watek drugi: zasypiam, zwalniam zasob i czekam na 5\n");
		pthread_cond_wait(&cond, &mutex);
	}
	
	printf("watek drugi: Zajmuje zasob.  Robie cos bo bylo 5\n");
	pthread_mutex_unlock(&mutex);
	printf("watek drugi: zwolnilem zasob\n");
	
	return NULL;
}

int main() {
	
	int i;
	pthread_t thread;
	
	pthread_create(&thread,NULL,&write_this,NULL);
	
	for(i = 0; i < 8; i++) {
		
		sleep(1);
		pthread_mutex_lock(&mutex);
		printf("watek pierwszy: zajalem zasob\n");
		a++;
		printf("a=%d\n",a);	
		
		if(a == 5) {
			pthread_cond_signal(&cond);
			printf("watek pierwszy: wyslalem sygnal\n");
		}
		
		sleep(1);
		pthread_mutex_unlock(&mutex);
		printf("watek pierwszy: zwolnilem zasob\n");
	}

	pthread_join(thread, NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	
	return EXIT_SUCCESS;	
}	
	
