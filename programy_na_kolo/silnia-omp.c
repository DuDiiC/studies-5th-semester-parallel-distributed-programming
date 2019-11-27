#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    int i, n;
    int result = 1, local_result = 1;

    scanf("%d", &n);

    # pragma omp parallel firstprivate(local_result)
    {
        #pragma omp for nowait
        for(i = 2; i <= n; i++) {
            local_result *= i;
        }

        #pragma omp critical
        result *= local_result;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}
