#Assignment 3 - Sorting

In this program, we are implementing four different types of sorting orders of insertion, quick, shell, and heap sort. We are also gathering statistics by collecting the number of moves and compares. 


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


