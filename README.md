# 1. Biblioteka **pthread**

---

##### NAGŁÓWEK:	
```c
#include <pthread.h>
```
##### KOMPOLACJA: 
    gcc [program] -lpthread

---

### Podstawowe operacje na wątkach

```c
/* zmienna wątku */
pthread_t thread;

/* tworzenie wątku */
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void*), void *arg);

/* czekanie na zakończenie wątku przez wątek wywołujący */
int pthread_join(pthread_t thread, void **retval);

/* oznacza wątek do usunięcia (odłączenia) ????? */
int pthread_detach(pthread_t thread);

/* kończy bieżący wątek z podaną wartością */
void pthread_exit(void *retval);

/* kończy podany wątek */
int pthread_cancel(pthread_t thread);

/* zmienia flagę stanu, która pozwala/zabrania 
 * kończenie wątku z zewnątrz funkcją pthread_cancel()
 * dostępne stany:
 * - PTHREAD_CANCEL_ENABLE
 * - PTHREAD_CANCEL_DISABLE
 **/
int pthread_setcancelstate(int state, int *oldstate);
```

---
---

Źródła:
1. [Konrad Siek - programowanie wielowątkowe w języku C](http://www.cs.put.poznan.pl/ksiek/sk2/pthreads.html)
2. [POSIX Threads - Wikibooks](https://pl.wikibooks.org/wiki/POSIX_Threads/Podstawowe_operacje)
3. [pthreads - linux man page](https://linux.die.net/man/7/pthreads)
4. [Skrypt do programowania równoległego i wielowątkowego AGH](http://www.metal.agh.edu.pl/~banas/PR/PRiR_skrypt.pdf)