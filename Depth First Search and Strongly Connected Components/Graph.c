/*********************************************************************************
*Julian Lafond, jmlafond
*2022 Winter CSE101 PA 3
*Graph.c
*Graph ADT
*********************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj 
{	
	List* L;
	int *color;
	int *parent;
	int *discover;
	int vertices;
	int edges;
	int time;
	int *finish;
} GraphObj;


Graph newGraph(int n)
{
	Graph create_graph = malloc(sizeof(GraphObj));		
	create_graph->L = malloc((n+1)*sizeof(List));
	create_graph->discover = (int*)malloc((n+1)*sizeof(int));
	create_graph->parent = (int*)malloc((n+1)*sizeof(int));
	create_graph->color = (int*)malloc((n+1)*sizeof(int));
	create_graph->finish = (int*)malloc((n+1)*sizeof(int));
	for (int i = 1; i < n + 1; i++)
	{
		create_graph->L[i] = newList();
		create_graph->discover[i] = UNDEF;
		create_graph->parent[i] = NIL;
		create_graph->color[i] = 2;   //2 = white, 3 = gray, 4 = black
		create_graph->finish[i] = UNDEF;
	}
	create_graph->time = 0;
	create_graph->vertices = n;
	create_graph->edges = 0;
	return create_graph;
}


void freeGraph(Graph* pG)
{
	if (pG == NULL)
	{
		fprintf(stderr, "Graph is empty");
		exit(1);
	}
	for (int i = 1; i < (*pG)->vertices + 1; i++)
	{
		freeList(&((*pG)->L[i]));
	}
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->finish);
 	free(*pG);
 	*pG = NULL;
}

int getOrder(Graph G)
{
	if (G == NULL)
        {       
                fprintf(stderr, "Cannot call getSize(),Graph is empty");
	       	exit(1);
	}
	return G->vertices;
}

int getSize(Graph G)
{
	if (G == NULL)
	{
		printf("Cannot call getSize(),Graph is empty");
	  	exit(1);
	}
        return G->edges;
}

int getParent(Graph G, int u)
{
	if (G == NULL)
	{
		fprintf(stderr, "Cannot getParent(), Graph is empty");
		exit(1);
	}	
	else if (u < 1 || u > getOrder(G))
        {
                fprintf(stderr, "Input vertices is greater than vertices allocated for");
        	exit(1);
	}
	return G->parent[u];
}

int getDiscover(Graph G, int u)
{
	if (G == NULL)
	{
		fprintf(stderr, "Cannot getDist(), Graph is empty");
		exit(1);
	}
	if (u < 1 || u > getOrder(G))
        {
                fprintf(stderr, "Input vertices is greater than vertices allocated for");
        	exit(1);
	}
	return G->discover[u];	
}


int getFinish(Graph G, int u)
{
        if (G == NULL)
        {
                fprintf(stderr, "Cannot getParent(), Graph is empty");
                exit(1);
        }
        else if (u < 1 || u > getOrder(G))
        {
                fprintf(stderr, "Input vertices is greater than vertices allocated for");
                exit(1);
        }
        return G->finish[u];
}

void add(Graph G, ListObj *list, int x)
{
	moveFront(list);
	while(index(list) >= 0)
	{
		if (x == get(list))
		{		
			return;
		}
		else if (get(list) > x)
		{
			insertBefore(list, x);
			return;
		}
		else 
		{
		  	moveNext(list);
		}
	}
	append(list, x);
}

void addEdge(Graph G, int u, int v)
{
	if (G == NULL)
        {       
                fprintf(stderr, "Graph is empty");
                exit(1);
        }
        else if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G))
        {
                fprintf(stderr, "Given vertices is out of range");
       		exit(1);
	 }
        else
        {
          	add(G, G->L[u], v);   
        	add(G, G->L[v], u);
	}
	G->edges+=1;

}


void addArc(Graph G, int u, int v)
{
	
	if (G == NULL)
        {       
                fprintf(stderr, "Graph is empty");
                exit(1);
        }
	if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G))
        {
                fprintf(stderr, "Given vertices is out of range");
       		exit(1);
	}
	add(G, G->L[u], v);	
	G->edges+=1;
}


void Visit(Graph G, int i, List S)
{
        if (G->L[i] == NULL)
        {
                fprintf(stderr, "Graph list Is empty");
                exit(1);
        }
        G->discover[i] = ++(G->time);
        G->color[i] = 3;
        moveFront(G->L[i]);
        while (index(G->L[i]) > -1)
	{
                int ind = get(G->L[i]);
                if (G->color[ind] == 2)
                {
                        G->parent[ind] = i;
                        Visit(G, ind, S);
                }
                moveNext(G->L[i]);
        }
        G->color[i] = 4;
        G->finish[i] = ++(G->time);
        insertAfter(S, i);
}

void DFS(Graph G, List S)
{
        if (G == NULL)
        {
                fprintf(stderr, "Graph is empty");
                exit(1);
        }
	if (S == NULL)
	{
		fprintf(stderr, "List is empty");
		exit(1);
	}
        if (length(S) != getOrder(G))
        {
                fprintf(stderr, "Vertices error");
                exit(1);
        }
        for (int i = 1; i < G->vertices + 1; i++)
        {
                G->color[i] = 2;
                G->parent[i] = NIL;
        }
        G->time = 0;
	moveBack(S); 
        for (int i = 0; i < length(S); i++)
	{
                int x = front(S);
                if (G->color[x] == 2)
                {
                        Visit(G, x, S);
                }
                deleteFront(S);
        }
}

Graph transpose(Graph G)	
{
	if (G == NULL)
        {
                fprintf(stderr, "Empty Graph");  
                exit(1);
        } 
        Graph n = newGraph(getOrder(G));
        for(int i = 1; i < getOrder(G) + 1; i++)
        {
		moveFront(G->L[i]);
		while(index(G->L[i]) >= 0)
		{
			int ind = get(G->L[i]);
                        addArc(n, ind, i);
			moveNext(G->L[i]);
		}
        }
        return n;
	
}

Graph copyGraph(Graph G)
{
	if (G == NULL)
        {
                fprintf(stderr, "Empty Graph"); 
                exit(1);
        }
	Graph n = newGraph(getOrder(G));
        for(int i = 1; i < getOrder(G) + 1; i++)
        {
                moveFront(G->L[i]);
		while(index(G->L[i]) >= 0)
                {	
			int ind = get(G->L[i]);
			addArc(n, i, ind);
                        moveNext(G->L[i]);
                }
        }
        return n;
}

void printGraph(FILE *out, Graph G)
{
	if (G == NULL)
        {       
                fprintf(stderr, "Graph is empty");
                exit(1);
        }
  	for (int i = 1; i < G->vertices + 1; i+=1)
	{
		List L = G->L[i];
    		fprintf(out, "%d: ", i);
		printList(out, L);	
		fprintf(out, "\n");
	}
}
