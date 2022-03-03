#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"


typedef struct GraphObj 
{
	ListObj** List;
	int *color;
	int *parent;
	int *distance;
	int vertices;
	int edges;
	int source;	

} GraphObj;

Graph newGraph(int n)
{
	GraphObj* create_graph = (struct GraphObj*)malloc(sizeof(struct GraphObj));		
	create_graph->List = (struct ListObj**)calloc(n + 1, sizeof(ListObj) * (n+1));
	create_graph->distance = (int*)calloc(n + 1, sizeof(int) * (n+1));
	create_graph->parent = (int*)calloc(n + 1, sizeof(int) * (n+1));	
	create_graph->color = (int*)calloc(n + 1, sizeof(int) * (n+1));
	for (int i = 1; i < n + 1; i++)
	{
		create_graph->List[i] = newList();
		create_graph->distance[i] = INF;
		create_graph->parent[i] = NIL;
		create_graph->color[i] = 2;   //2 = white, 3 = gray, 4 = black
	}
	create_graph->vertices = n;
	create_graph->edges = 0;
	create_graph->source = NIL;
	return create_graph;

}

void freeGraph(Graph* pG)
{
	for (int i = 1; i < (*pG)->vertices + 1; i++)
	{
		freeList(&((*pG)->List[i]));
	}
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->distance);
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
		fprintf(stderr, "Cannot call getSize(),Graph is empty");
		exit(1);
	}
	return G->edges;
}

int getSource(Graph G)
{
	if (G == NULL)
	{
		fprintf(stderr, "Cannot call getSource(), Graph is empty");
		exit(1);
	}
	if (G->source == NIL)
	{
		return NIL;
	}
	return G->source;
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


int getDist(Graph G, int u)
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
	return G->distance[u];
	
}

void getPath(List L, Graph G, int u)
{
	if (G == NULL)
	{
		fprintf(stderr, "Cannot getPath(), Graph is empty");
		exit(1);
	}
	if (u < 1 || u > getOrder(G))
	{
		fprintf(stderr, "Input11 vertices is greater than vertices allocated for");
		exit(1);
	}
	if (G->source == NIL)
	{
		fprintf(stderr, "Must call bfs first");
		exit(1);
	}
	if (G->source == u)
	{
		append(L,u);
	}
	else if (G->parent[u] == NIL)
	{
		append(L, NIL);
	}
	else 
	{
		getPath(L, G, G->parent[u]);
		append(L,u);
	}	
	
}

void reset(int *array, int length)
{
	for (int i = 1; i < length; i++)
	{
		array[i] = 0;
	}
}

void makeNull(Graph G)
{
	if (G == NULL)
	{
		fprintf(stderr, "Cannot getPath(), Graph is empty");
                exit(1);
	}
		
	for (int i = 1; i < G->vertices; i++)
	{
		clear(G->List[i]);
	}
	reset(G->color, G->vertices);
	reset(G->parent, G->vertices);
	reset(G->distance, G->vertices);
 	G->edges = 0;
	G->source = NIL;
	G->vertices = 0;
}
	



void add(Graph G, ListObj *list, int x)
{
//	G->edges+=1;
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

        if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G))
        {
                fprintf(stderr, "Given vertices is out of range");
       		exit(1);
	 }
        else
        {
                add(G, G->List[u], v);   
        	add(G, G->List[v], u);
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
	else
	{
		add(G, G->List[u], v);	
	}
	G->edges+=1;
}
	
			
void BFS(Graph G, int s)
{	
	if (G == NULL)
	{
		fprintf(stderr, "Graph is empty");
		exit(1);
	}
	if (s < 1 || s > getOrder(G))
	{
		fprintf(stderr, "Given vertices is out of range");
		exit(1);
	}
	G->source = s;
	for (int i = 1; i <= G->vertices; i++)
	{
		G->color[i] = 2;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = 3;
	G->distance[s] = 0;
	G->parent[s] = NIL;	
	List List1 = newList();
	append(List1, s);
	moveFront(List1);
	while(index(List1)!=-1)
	{
		int x = get(List1);
		moveFront(G->List[x]);
		while (index(G->List[x])!=-1)
		{
			int ind = get(G->List[x]);
			if (G->color[ind] == 2)
			{	
				G->color[ind] = 3;
				G->distance[ind] = G->distance[x] + 1;
				G->parent[ind] = x;
				append(List1,ind);
			}
			moveNext(G->List[x]);
		}
	G->color[x] = 4;
	moveNext(List1);
	}
	freeList(&List1);

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
		List L = G->List[i];
    		printf("%d: ", i);
		printList(out, L);	
		printf("\n");
	} 
	printf("\n");
}

