#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define OPTIONS "aisqer:gn:gp:gh"

void printarray(uint32_t *A, uint32_t elements) {

    for (uint32_t i = 0; i < elements; i++) {
        if (i % 5 == 0) {
            printf("\n");
        }
        printf("%13" PRIu32, A[i]);
    }
}

typedef enum { HEAP, SHELL, INSERTION, QUICK } Sorts;
const char *names[] = { "heap sort", "shell sort", "insertion sort", "quick sort" };

int main(int argc, char **argv) {
    Set s = empty_set();
    uint32_t seed = 13371453;
    bool entered_while_loop = false;
    uint32_t size = 100;
    int opt = 0;
    uint32_t elements = 100; //number of elements to print
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        entered_while_loop = true;
        switch (opt) {
        case 'a':
            s = insert_set(HEAP, s);
            s = insert_set(SHELL, s);
            s = insert_set(INSERTION, s);
            s = insert_set(QUICK, s);
            break;
        case 'i': s = insert_set(INSERTION, s); break;
        case 's': s = insert_set(SHELL, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'e': s = insert_set(HEAP, s); break;
        case 'r': seed = atoi(optarg); break;
        case 'n': size = atoi(optarg); break;
        case 'p': elements = atoi(optarg); break;
        case 'h':
            printf(
                "Select at least one sort to perform. \nSYNOPSIS\nA collection of comparison-based "
                "sorting algorithms.\n\nUSAGE \n./sorting [-haeisqn:p:r:] [-n length] [-p "
                "elements] [-r seed]\n\nOPTIONS\n\n-h         display program help and usage.-a    "
                "          enable all sorts.\n-e              enable Heap Sort.\n-i              "
                "enable Insertion Sort.\n-s              enable Shell Sort.\n-q              "
                "enable Quick Sort.\n-n length       specify number of array elements (default: "
                "100).\n-p elements     specify number of elements to print (default: 100).\n-r "
                "seed         specify random seed (default: 13371453).\n");
            break;
        }
    }
    if (!entered_while_loop) {
        printf("Select at least one sort to perform. \nSYNOPSIS\nA collection of comparison-based "
               "sorting algorithms.\n\nUSAGE \n./sorting [-haeisqn:p:r:] [-n length] [-p elements] "
               "[-r seed]\n\nOPTIONS\n\n-h         display program help and usage.-a              "
               "enable all sorts.\n-e              enable Heap Sort.\n-i              enable "
               "Insertion Sort.\n-s              enable Shell Sort.\n-q              enable Quick "
               "Sort.\n-n length       specify number of array elements (default: 100).\n-p "
               "elements     specify number of elements to print (default: 100).\n-r seed         "
               "specify random seed (default: 13371453).\n");
    }

    for (uint32_t x = HEAP; x <= QUICK; x += 1) {
        Stats stats;
        stats.moves = 0;
        stats.compares = 0;
        srand(seed);
        uint32_t *A = (uint32_t *) calloc(1, sizeof(uint32_t) * size);
        for (uint32_t i = 0; i < size; i++) {
            A[i] = rand() % 1073741823; //aaply a bitmask so each random number is in 30 - bits
        }
        //if num elements to print is greater than size, that would cause an error
        if (elements > size) {
            elements = size;
        }
        if (member_set(x, s)) {
            if (x == 0) {
                heap_sort(&stats, A, size);
                printf("Heap Sort, ");
            }
            if (x == 1) {
                shell_sort(&stats, A, size);
                printf("Shell Sort, ");
            }
            if (x == 2) {
                insertion_sort(&stats, A, size);
                printf("Insertion Sort, ");
            }
            if (x == 3) {
                quick_sort(&stats, A, size);
                printf("Quick Sort, ");
            }
            if (x == 4) {

                heap_sort(&stats, A, size);
                shell_sort(&stats, A, size);
                insertion_sort(&stats, A, size);
                quick_sort(&stats, A, size);
            }
            printf("%" PRIu32 " elements, ", size);
            printf("%" PRIu64 " moves, ", stats.moves);
            printf("%" PRIu64 " compares ", stats.compares);
            printarray(A, elements);
            if (elements != 0) {
                printf("\n");
            }
            free(A);
            A = NULL;
        }
    }
}
