#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>  
#include "List.h"
#include "Graph.h"

      
int main(int argc, char*argv[])
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
	struct GraphObj* graph = newGraph(v);
	int j;
	int i;
	while(!feof(in))
	{
		fscanf(in, "%d %d", &i, &j);	
		if (i > 0 && j > 0)
		{
			addEdge(graph, i, j);
		}
		else if (i == 0 || j == 0)
		{
			break;
		}
	}
	printGraph(stdout, graph);
	int m, n;
	while(!feof(in))
	{
		
		fscanf(in, "%d %d", &m, &n);
		if (m > 0 && n > 0)
		{
			BFS(graph,m);
			printf("\nThe distance from %d to %d is %d", m, n, getDist(graph, n));
			printf("\nA shortest %d-%d path is: ", m, n);
			List newL = newList();
			getPath(newL, graph, n);
			printList(stdout, newL);			
			printf("\n");	
		}
		else if (m == 0 || n == 0)
		{
			break;
		}
		
	}
	printf("\n");
	fclose(in);
	return 0;
}
