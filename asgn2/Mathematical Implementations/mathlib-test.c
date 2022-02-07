#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh"
#include "mathlib.h"

#include <math.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    int opt = 0;
    bool stats = false;

    //determine if s
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        if (opt == 's') {
            stats = true;
        }
    }

    // reset parsing
    optind = 0;

    //some boolean to check if you ever go in the while loop
    bool entered_while_loop = false;
    //process funtions while loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        entered_while_loop = true;
        //set boolean to true for goign in while loop
        switch (opt) {
        case 'a':
            printf(
                "e() =  %16.15lf, M_E = %16.15lf, diff = %16.15f\n", e(), M_E, absolute(e() - M_E));
            printf("pi_euler() =  %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
                absolute(pi_euler() - M_PI));
            printf("pi_bbp() =  %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
                absolute(pi_bbp() - M_PI));
            printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(),
                M_PI, absolute(pi_madhava() - M_PI));
            printf("pi_viete() =  %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
                absolute(pi_viete() - M_PI));
            for (double i = 0; i <= 10; i += 0.1) {
                printf("sqrt_newton(%0.6f) =  %16.15lf, sqrt(%0.6f) =  %16.15lf, diff = %16.15lf\n",
                    i, sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
            }
            break;
        case 'e':
            printf(
                "e() =  %16.15lf, M_E = %16.15lf, diff = %16.15f\n", e(), M_E, absolute(e() - M_E));
            if (stats == true) {
                printf("e terms = %d\n", e_terms());
            }
            break;
        case 'b':
            printf("pi_bbp() =  %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
                absolute(pi_bbp() - M_PI));
            if (stats == true) {
                printf("pi_bbp() terms = %d\n", pi_bbp_terms());
            }
            break;
        case 'm':
            printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(),
                M_PI, absolute(pi_madhava() - M_PI));
            if (stats == true) {
                printf("pi_madhava() terms = %d\n", pi_madhava_terms());
            }
            break;
        case 'r':
            printf("pi_euler() =  %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
                absolute(pi_euler() - M_PI));
            if (stats == true) {
                printf("pi_euler() terms = %d\n", pi_euler_terms());
            }
            break;
        case 'v':
            printf("pi_viete() =  %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
                absolute(pi_viete() - M_PI));
            if (stats == true) {
                printf("pi_viete() terms = %d\n", pi_viete_factors());
            }
            break;
        case 'n':
            for (double i = 0; i <= 10; i += 0.1) {
                printf("sqrt_newton(%0.6f) =  %16.15lf, sqrt(%0.6f) =  %16.15lf, diff = %16.15lf\n",
                    i, sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
            }
            break;
        case 'h':
            printf("  SYNOPSIS\n A test harness for the small numerical library. \nUSAGE "
                   "./mathlib-test [-aebmrvnsh] \n OPTIONS \n -e   Runs e test. \n  -b   Runs BBP "
                   "pi test. \n -m   Runs Madhava pi test. \n -r   Runs Euler pi test. \n -v   "
                   "Runs Viete pi test. \n -n   Runs Newton square root tests. \n -s   Print "
                   "verbose statistics. \n -h   Display program synopsis and usage. \n");
            break;
        }
    }

    // if enter_while_loop is false, print out the help statement
    // otherwise do nothing
    if (!entered_while_loop) {
        printf("  SYNOPSIS\n A test harness for the small numerical library. \nUSAGE "
               "./mathlib-test [-aebmrvnsh] \n OPTIONS \n -e   Runs e test. \n  -b   Runs BBP pi "
               "test. \n -m   Runs Madhava pi test. \n -r   Runs Euler pi test. \n -v   Runs Viete "
               "pi test. \n -n   Runs Newton square root tests. \n -s   Print verbose statistics. "
               "\n -h   Display program synopsis and usage. \n");
    }

    //if the boolean for entering while loop is false then print out help statement
}
