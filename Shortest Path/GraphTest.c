#include <stdlib.h>
#include "List.h"
#include "Graph.h"


int main() {
  struct GraphObj* graph = newGraph(6);
  addEdge(graph, 1, 2);
  addEdge(graph, 1, 3);
  addEdge(graph, 2, 4);
  addEdge(graph, 2, 5);
  addEdge(graph, 2, 6);
  addEdge(graph, 3, 4);
  addEdge(graph, 4, 5);
  addEdge(graph, 5, 6);
  BFS(graph, 1);
  printf("Number of vertices is %d", getOrder(graph));
  printf("\nNumber of edges is %d", getSize(graph));
  printf("\nSource is %d", getSource(graph));
  printf("\nParent is %d", getParent(graph, 2));
  printf("\nDistance is %d", getDist(graph, 6));
  List new_list = newList();
  getPath(new_list, graph, 4);
  printf("\n");
  printList(stdout, new_list);          
  printf("\n");
  printGraph(stdout, graph);
  return 0; 
}




