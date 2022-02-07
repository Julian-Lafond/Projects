#include <stdio.h>
#define EPSILON 1e-14
#include "mathlib.h"

static int increment;

double e(void) {

    double taylor;
    increment = 0;
    double fact = 1;
    double add = 1;
    for (int i = 1;; i++) {
        fact = fact * i; //fact =
        taylor = 1 / fact;
        if (EPSILON > taylor) //cant you use a while loop (while taylor > epsilon)
        {
            break;
        }
        add += taylor;
        increment += 1;
        //also you want to find a way to use the previous factorial and multiply that to the iteration.
    }
    //printf("Taylor series: %.60f\n", add);
    return add;
}

int e_terms(void) {
    return increment;
}
