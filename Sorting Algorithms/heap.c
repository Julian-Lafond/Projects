//This heap sort program was inspired by the pseudocode provided by Prof Long
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int max_child(Stats *stats, uint32_t *A, uint32_t beg, uint32_t end) {
    uint32_t left = 2 * beg;
    uint32_t right = left + 1;
    if (right <= end && A[right - 1] > A[left - 1]) {
        cmp(stats, A[right - 1], A[left - 1]);
        cmp(stats, A[right - 1], A[left - 1]);
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t beg, uint32_t end) {
    bool disc = false;
    uint32_t first = beg;
    uint32_t high;
    high = max_child(stats, A, first, end);
    while (first <= end / 2 && !disc) {
        if (cmp(stats, A[first - 1], A[high - 1]) == -1) {
            swap(stats, &A[first - 1], &A[high - 1]);
            first = high;
            high = max_child(stats, A, first, end);
        } else {
            disc = true;
        }
    }
}
void build_heap(Stats *stats, uint32_t *A, uint32_t beg, uint32_t end) {
    for (uint32_t i = end / 2; i > beg - 1; i -= 1) {
        cmp(stats, i, end);
        fix_heap(stats, A, i, end);
    }
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t beg = 1;
    uint32_t la = n;
    build_heap(stats, A, beg, la);
    for (uint32_t la = n; la > beg; la -= 1) {
        swap(stats, &A[beg - 1], &A[la - 1]);
        fix_heap(stats, A, beg, la - 1);
    }
}
