#Assignment 1 - Pass the Pigs

Pass the Pigs

This program is a self-playing implementation game in which up to 10 players roll a pig and gain points until a player reaches 100 points. Each player may roll the pig until they land on its side.

Points are given as shown:

BACK 10 points

SNOUT 15 points

UPRIGHT 10 points

EARS 5 points

SIDE End Turn

Building

To build the program:

$ clang -Wall -Wextra -Wpendatic -Werror -o pig pig.c names.h

#Running

To run the program:

$ ./pig

