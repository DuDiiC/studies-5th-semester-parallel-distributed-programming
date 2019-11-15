/* liczy jakies chore rzeczy :o */

#define _GNU_SOURCE

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <math.h> /* -lm */

int GetCPUCount() {
	cpu_set_t cs;
 	int i, count = 0;
 	CPU_ZERO(&cs);
 	sched_getaffinity(0, sizeof(cs), &cs);
 	for(i = 0; i < 8; i++) {
  		if(CPU_ISSET(i, &cs)) {
   			count++;
		}
 	}

 	return count;
}

double waste_time(long n) {
	double res = 0;
	long i = 0;
	while (i < n * 200000) {
		i++;
	    res += sqrt(i);
	}

	return res;
}

void *thread_func_1(void *ptr) {
	cpu_set_t mask; 
	CPU_ZERO(&mask);
    CPU_SET(0, &mask);
	if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
		perror("pthread_setaffinity_np");
	printf("Policzylem %f na CPU %d\n", waste_time(10000), sched_getcpu());
	CPU_ZERO(&mask);
    CPU_SET(1, &mask);
	if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
		perror("pthread_setaffinity_np");
	printf("Policzylem %f na CPU %d\n", waste_time(10000), sched_getcpu());
	return NULL;
}

void *thread_func_2(void *ptr) {
	cpu_set_t mask;
	CPU_ZERO(&mask);
    CPU_SET(1, &mask);
	if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
		perror("pthread_setaffinity_np");
	printf("Policzylem %f na CPU %d\n", waste_time(20000), sched_getcpu());
	return NULL;
}
int main(){
	pthread_t thread1, thread2;
	
	if(GetCPUCount() < 2) 
		return EXIT_FAILURE;
	
	pthread_create(&thread1, NULL, thread_func_1, NULL);
	pthread_create(&thread2, NULL, thread_func_2, NULL);
	pthread_join(thread1, NULL);	
	pthread_join(thread2, NULL);	
	
	return EXIT_SUCCESS;
}
