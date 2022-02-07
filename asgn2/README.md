#Assignment 2 - A Little Slice of Pi

In this program, we are implementing various mathematical functions and using them to compute the fundamental constants of e and pi. A test harness was also built to compare the the implemented functions to the math library.  

#Building

To build the program:

$ clang -Wall -Wextra -Wpendatic -Werror -o mathlib mathlib-test.c bbp.c e.c euler.c madhava.c mathlib.h newton.c viete.c

#Running

To run the program

$./mathlib-test -command line option

Use the following command line options:

 -a: Runs All Tests.
 -e: Runs Approximation Test.
 -b: Runs Bailey-Borwein-Plouffe π approximation test.
 -m: Runs Madhava π approximation test.
 -r: Runs Euler sequence π approximation test.
 -v: Runs Viète π approximation test.
 -n: Runs Newton-Raphson Square Root Approximation Tests.
 -s: Enable printing of statistics to see computed terms and factors foreach nested function. 
 -h: Display A Help Message Detailing Program Usage.

