#Assignment 2

List.c - Doubly linked list implementation
List.h - Header files
Graph.c - Graph tree implementation 
Graph.h - Header files 
GraphTest.c - Test cases for Graph
FindPath.c - Reads from textfile and prints adjacency list and shortest path
Makefile - compiles 

#Note to Grader
In PA1 and PA2, I could not run the ModelListTest.c with the following issue:

List.h:31:5: error: conflicting types for ‘index’; have ‘int(struct ListObj *)’
   31 | int index(List L);  // Returns index of cursor element if defined, -1 otherwise.
      |     ^~~~~
In file included from ModelListTest.c:4:
/usr/include/string.h:485:14: note: previous declaration of ‘index’ with type ‘char *(const char *, int)’
  485 | extern char *index (const char *__s, int __c)
      |              ^~~~~

I used filezilla and ran on timeshare.

This is the second assignment where I have not been able to test my functions. I've asked multiple TAs about this issue and none of them could resolve it.

I hope you understand my issue and still receive credit for my program. 

Thank you.
