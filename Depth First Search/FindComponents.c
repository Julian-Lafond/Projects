/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 3
* FindComponents.c
* GraphClient for Graph.c
**********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#include <stdint.h>


int main(int argc, char* argv[])
{
    FILE *in, *out;
    if (argc !=  3)
    {       
          printf("Usage: %s <input file> <output file>\n", argv[0]);
          exit(1);
    }       
    in = fopen(argv[1], "r");
    if (in == NULL)
    {        
          printf("Unable to open file %s for reading\n", argv[1]);
          exit(1);
    }
    out = fopen(argv[2], "w");
    if (out == NULL)
    {
          printf("Unable to open file %s for writing\n", argv[2]);
          exit(1);
    }
    int v = 0;
    fscanf(in, "%d", &v);
    Graph G = newGraph(v);      
    int j;
    int i;
    while(!feof(in))
    {
        fscanf(in, "%d %d", &i, &j);    
        if (i > 0 && j > 0)
        {
             addArc(G, i, j);
        }
        else if (i == 0 || j == 0)
        {
              break;
        }
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    List S = newList();
    for(int i = 1; i <= getOrder(G); i++)
    {
	 append(S, i);
    }
    DFS(G, S);
    Graph tran = transpose(G);
    DFS(tran, S);
    int count = 0;
    for(int i = 1; i <= getOrder(tran); i++)
    {
        if(getParent(tran, i) == NIL)
	{
            count+=1;
        }
    }
    fprintf(out, "\nG contains %d strongly connected components:", count);
    List L = newList();
    moveBack(S);
    for(int i = 1; i <= count; i++)
    {
        while(getParent(tran, get(S)) != NIL)
	{
            prepend(L, get(S));
            movePrev(S);
        }
        prepend(L, get(S));
        movePrev(S);
        fprintf(out, "\nComponent %d: ", i); 
        printList(out, L);
    	fprintf(out, "\n");
	clear(L);
    }	
    fprintf(out, "\n");
    freeList(&S);
    freeGraph(&G);
    freeGraph(&tran);
    fclose(in);
    fclose(out);
}

