#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

static int increment = 1;

double pi_madhava(void) {
    double alt = 1.0;
    double add = 1.0;
    double part = 1.0;
    double i = 1.0;
    double final;
    while (absolute(part) > EPSILON) {
        alt = alt / -3.0;
        part = alt / (2.0 * i + 1.0);
        add = add + part;
        increment += 1;
        i += 1;
    }
    final = add * sqrt_newton(12.0);
    return final;
}

int pi_madhava_terms(void) {
    return increment;
}
