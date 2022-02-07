#include <stdio.h>
#define EPSILON 1e-14

int static increment;

double pi_bbp(void) {
    increment = 0;
    double start = 0.0;
    double div = 1.0;
    double bbp = 1.0;
    double i = 0;
    while (bbp > EPSILON) {
        double num1 = (4.0 / (8.0 * i + 1.0));
        double num2 = (2.0 / (8.0 * i + 4.0));
        double num3 = (1.0 / (8.0 * i + 5.0));
        double num4 = (1.0 / (8.0 * i + 6.0));
        if (i == 0) {
            div = 1;
            bbp = div * (num1 - num2 - num3 - num4);
        } else {
            div /= 16.0;
            bbp = div * (num1 - num2 - num3 - num4);
        }
        start += bbp;
        increment += 1;
        i += 1;
    }
    return start;
}

int pi_bbp_terms(void) {
    return increment;
}
