/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 3
* GraphTest.c
* Graph test for Graph ADT
**********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#include <stdint.h>
/*
int main(int argc, char *argv[])
{
        struct GraphObj* G = newGraph(5);        
	List S = newList();
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 1, 4);
	addArc(G, 3, 4);
	addArc(G, 2, 4);
	addEdge(G, 1, 5);
	DFS(G, S);
	printf("Number of vertices is %d\n", getOrder(G));
	printf("Number of edges is %d\n", getSize(G));
	for (int i = 1; i < getOrder(G)+ 1; i++)
	{
		printf("Parent is %d\n", getParent(G, i));
		printf("Discover is %d\n", getDiscover(G, i));
		printf("Finish is %d\n", getFinish(G, i));
	}
	struct GraphObj* transp = transpose(G);
        DFS(transp, S);
	copyGraph(G);
	freeGraph(&G);
}

*/
