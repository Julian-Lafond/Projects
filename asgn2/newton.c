#include <stdio.h>
#define EPSILON 1e-14
#include "mathlib.h"

static int increment;

double sqrt_newton(double x) {
    double z = 0.0;
    double y = 1.0;
    increment = 0;
    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
        increment += 1;
    }
    return y;
}

int sqrt_newton_iters(void) {
    return increment;
}
