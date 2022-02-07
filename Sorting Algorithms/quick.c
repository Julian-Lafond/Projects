//This quick sort program was inspired by the pseudocode given to us by Prof Long
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int partition(Stats *stats, uint32_t *A, uint32_t min, uint32_t n) {
    int i = min - 1;
    for (uint32_t j = min; j < n; j++) {
        if (cmp(stats, A[j - 1], A[n - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[n - 1]);
    return i + 1;
}

void quick_sorter(Stats *stats, uint32_t *A, uint32_t min, uint32_t n) {
    if (min < n) {
        uint32_t pi = partition(stats, A, min, n);
        quick_sorter(stats, A, min, pi - 1);
        quick_sorter(stats, A, pi + 1, n);
    }
}
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
