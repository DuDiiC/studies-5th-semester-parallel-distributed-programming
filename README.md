# Biblioteka **pthread**

---

### NAGŁÓWEK:	`pthread.h`
### TYP WĄTKU:	`pthread_t`
### FLAGA KOMPOLACJI: `-lpthread`

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