#include <stdio.h>
#define EPSILON 1e-14
#include "mathlib.h"

static float increment;

double pi_viete(void) {
    increment = 0;
    double add = 1.0;
    double front = 0.0;
    double ptr = 0.0;
    while (absolute(ptr - 1) > EPSILON) {
        ptr = sqrt_newton(2 + front);
        front = ptr;
        ptr = ptr / 2;
        add = add * ptr;
        increment += 1;
    }
    double final = 2 / add;
    return final;
}
int pi_viete_factors(void) {
    return increment;
}
