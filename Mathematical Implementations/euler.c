#include <stdio.h>
#define EPSILON 1e-14
#include "mathlib.h"

static int increment;

double pi_euler(void) {
    double taylor = 1.0;
    increment = 0;
    double fact = 1.0;
    double newfact;
    double add = 0.0;
    double i = 1.0;
    double multiply;
    while (taylor > EPSILON) {
        newfact = fact * i;
        taylor = 1.0 / newfact;
        add = add + taylor;
        increment += 1;
        fact += 1;
        i += 1;
    }
    multiply = 6.0 * add;
    double sqrt = sqrt_newton(multiply);
    return sqrt;
}

int pi_euler_terms(void) {
    return increment;
}
