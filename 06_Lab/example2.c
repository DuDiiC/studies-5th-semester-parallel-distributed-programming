#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	
	int sm = -2;
	float il = -1;
	
	printf("sm: %d, il: %f\n", sm, il);

	/* od operatora ktory wpiszemy w reduction zalezy jaka bedzie poczatkowa wartosc zmiennej (np. dla sm bedzie 0, dla il bedzie 1.000000
	 * koncowy wynik zapisywany do zmiennej powyzej czesci rownoleglej, ktora byla podana wyzej
	 * w kazdym watku wykonywane sa dane operacje */
	#pragma omp parallel reduction(+: sm) reduction(*: il)
	{
		printf("\tsm: %d, il: %f\n", sm, il);

		sm += 4;
		il *= 2;

		printf("\t\tsm: %d, il: %f\n", sm, il);
	}

	printf("\t\t\tsm: %d, il: %f\n", sm, il);

	return EXIT_SUCCESS;
}
