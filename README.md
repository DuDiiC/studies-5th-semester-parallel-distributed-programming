> UWAGA: Pisanie tego dokumentu zostało zakończone - zajmowało zdecydowanie zbyt dużo czasu, w stosunku do efektów dydaktycznych.

# 1. Biblioteka **`pthread`**

#### NAGŁÓWEK:	
```c
#include <pthread.h>
```
#### KOMPILACJA: 
    gcc [program] -lpthread

## Podstawowe operacje na wątkach

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

/* przeprowadza test, czy nie ma zadania odwolania i 
 * ewentualnie odpowiednio reaguje w razie jego istnienia */
void pthread_testcancel(void);
```

## Mutexy

```c
/* zmienna mutexu z inicjalizacją */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* */
int pthread_mutex_lock(pthread_mutex_t *mutex);

/* */
int pthread_mutex_unlock(pthread_mutex_t *mutex);

/* */
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

## Warunki

```c
/* zmienna warunku z inicjalizacją */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/* */
int pthread_cond_signal(pthread_cond_t *cond);

/* */
int pthread_cond_broadcast(pthread_cond_t *cond);

/* */
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);

/* */
int pthread_cond_destroy(pthread_cond_t *cond);
```

## Bariery

```c
/* zmienna bariery */
pthread_barrier_t barrier;

/* */
int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned count);

/* */
int pthread_barrier_wait(pthread_barrier_t *barrier);

/* */
int pthread_barrier_destroy(pthread_barrier_t *barrier);
```
# 2. Biblioteka **`OpenMP`**

#### NAGŁÓWEK:	
```c
#include <omp.h>
```
#### KOMPILACJA: 
    gcc [program] -fopenmp

## Dyrektywy

```c
/* ustala liczbę wątków */
void omp_set_num_threads(int num_threads);

/* */
# pragma omp parallel 
{

}

/* */
# pragma omp parallel private(variable)
{

}

/* */
# pragma omp parallel firstprivate(variable)

/* */
# pragma omp for

/* */
# pragma omp for schedule(dynamic, 1)

/* */
# pragma omp for nowait

/* */
# pragma omp for wait

/* */
# pragma omp barrier

/* */
# pragma omp critical

/* */
# pragma omp master

/* */
# pragma omp atomic 

/* */
# pragma omp reduction(operator: varible)


```

---
---
---












## TWORZENIE WĄTKU:

```c
int pthread(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void*), void *arg);
```

- `*thread` - wskaźnik do wątku, który chcemy utworzyć  
- `*pthread_attr_t` - parametry wątku  
- `*start_routine` - funkcja, która wątek wykona  
- `*arg` - argument przekazywany w funkcji 'start_routine'

W przypadku odpowiedniego wykonania zwraca 0, kod błędu wpw.

---

## CZEKANIE NA ZAKOŃCZENIE WĄTKU:

```c
int pthread_join(pthread_t thread, void **retval);
```

- `thread` - wątek, na zakończenie którego czekamy
- `**retval` - adres, do którego ma zostać przypisana wartość zwracana przez wątek 'thread' (lub `NULL`)

W przypadku odpowiedniego wykonania zwraca 0, kod błędu wpw.  

> Każdy wątek powinien być połaczony z innym (np. glównym), ponieważ wątek zwalnia swoje zasoby dopiero w momencie wykonania na nim join'a.

---

## ODŁĄCZENIE WĄTKU:

```c
int pthread_detach(pthread_t thread);
```

- `thread` - wątek, który zamierzamy odłączyć

> Odłączony wątek zwraca wszystkie zasoby, mimo że nie wykonuje się (a nawet nie można) na nim join'a.

ZAKOŃCZENIE AKTUALNEGO WĄTKU:

```c
void pthread_exit(void *retval);
```

- `*retval` - wartość zwracana przez bieżący wątek

> Aby umożliwić innym wątkom pracę do samego końca, warto wątek główny (w funkcji `main`) kończyć wywołaniem `pthread_exit()`, zamiast `exit()`.

---

## KOŃCZENIE INNEGO WĄTKU

```c
int pthread_cancel(pthread_t thread);
```

- `thread` - wątek, który chcemy zakończyć

> Aby umożliwić wykonanie tej operacji, należy pozwolić zakończenie bieżącego wątku, poprzez zmianę flagi stanu przy użyciu funkcji:

```c
int pthread_setcancelstate(int state, int *oldstate);
```

- `state` - nowy stan wątku, do wyboru flagi: `PTHREAD_CANCEL_ENABLE`, `PTHREAD_CANCEL_DISABLE`
- `*oldstate` - poprzedni stan wątku

---
---

Źródła:
1. [Konrad Siek - programowanie wielowątkowe w języku C](http://www.cs.put.poznan.pl/ksiek/sk2/pthreads.html)
2. [POSIX Threads - Wikibooks](https://pl.wikibooks.org/wiki/POSIX_Threads/Podstawowe_operacje)
3. [pthreads - linux man page](https://linux.die.net/man/7/pthreads)
4. [Skrypt do programowania równoległego i wielowątkowego AGH](http://www.metal.agh.edu.pl/~banas/PR/PRiR_skrypt.pdf)
