/* 	program pokazuje w jaki sposob mozna wyslac sygnal zwolnienia
	zasobow do wiekszej ilosci watkow jednoczesnie ??? */

#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

int a = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* write_this(void* ptr) {
	pthread_mutex_lock(&mutex);
	printf("watek potomny: zajalem zasob\n");
	if(a!=5){
		printf("watek potomny: zasypiam, zwalniam zasob i czekam na 5\n");
		pthread_cond_wait(&cond,&mutex);
		printf("watek potomny: Zajmuje zasob. Robie cos bo bylo 5\n");
	}
	sleep(1);
	pthread_mutex_unlock(&mutex);
	printf("watek potomny: zwolnilem zasob\n");
	return NULL;
}
int main() {	
	
	int i;
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, &write_this, NULL);
	pthread_create(&thread2, NULL, &write_this, NULL);
	for(i = 0; i < 8; i++) {
		sleep(1);
		pthread_mutex_lock(&mutex);
		printf("watek macierzysty: zajalem zasob\n");
		a++;
		printf("a=%d\n", a);	
		if(a == 5) {
			/* wysylanie sygnalu do wszystkich watkow??? */
			pthread_cond_broadcast(&cond);
			printf("watek macierzysty: wyslalem sygnal\n");
		}
		sleep(1);
		pthread_mutex_unlock(&mutex);
		printf("watek macierzysty: zwolnilem zasob\n");
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	return EXIT_SUCCESS;	
}	
	
