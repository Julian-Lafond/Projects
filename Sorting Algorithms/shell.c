//This shell sort program was inspired by the pseudocode provided by Prof Long
#include "shell.h"
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint32_t *gaps(uint32_t n) {
    uint32_t *gap = (uint32_t *) malloc(n * sizeof(uint32_t));
    uint32_t beg = (log(3 + 2 * n) / log(3));
    uint32_t j = 0;
    for (uint32_t m = beg; m > 0; m--) {
        gap[j++] = ((pow(3, m) - 1) / 2);
    }
    return gap;
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t *gap = gaps(n);
    for (uint32_t i = 0; i < n; i++) {
        for (uint32_t l = gap[i]; l < n; l += 1) {
            uint32_t t = l;
            uint32_t ptr = move(stats, A[l]);
            while (t >= gap[i] && cmp(stats, ptr, A[t - gap[i]]) == -1) {
                A[t] = move(stats, A[t - gap[i]]);
                t -= gap[i];
            }
            A[t] = move(stats, ptr);
        }
    }
}
