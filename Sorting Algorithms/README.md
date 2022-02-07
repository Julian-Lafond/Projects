This progam implementes four sorting orders: insertion, quick, shell, and heap sort. A test harness is built to create an array of pseudorandam elements to test each sort. We gather statistics about each sort and its performance. The statistics contain the size of the array, the number of moves required, and the number of comaprisons required. 

#Building

To build the program:

$ clang -Wall -Wextra -Wpendatic -Werror -o sorting sorting.c heap.c insert.c quick.c shell.c stats.c

#Running

To run the program:

$./sorting -command line option

Use the following command line options:

-a : Employs all sorting algorithms. 

-e : Enables Heap Sort.

-i : Enables Insertion Sort.

-s : Enables Shell Sort.

-q : Enables Quicksort.

-r seed : Set the random seed to seed. The default seed should be 13371453.

-n size : Set the array size to size. The default size should be 100.

-p elements : Print out the number of elements from the array. The default number of elements to print out should be 100. If the size of the array is less than the specified number of elements to print, print out the entire array and nothing more.

-h : Prints out program usage. See reference program for example of what to print.


