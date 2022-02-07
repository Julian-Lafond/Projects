//This insertion sort program was inspired by the pseudocode given to us by Prof Long
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t j = 1; j < n; j++) {
        uint32_t sub = j;
        uint32_t set = move(stats, A[j]);
        while (sub > 0 && cmp(stats, set, A[sub - 1]) == -1) {
            A[sub] = move(stats, A[sub - 1]);
            sub -= 1;
        }
        A[sub] = move(stats, set);
    }
}
