// Dijkstra ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif

typedef struct PredNode {
   int         v;
   struct PredNode *next;
} PredNode;

typedef struct ShortestPaths {
   int noNodes;
   int src;
   int *dist;
   PredNode **pred;
} ShortestPaths;


/* Finds shortest paths from a given source vertex to all other vertices, as discussed in the lectures.

 * The function offers one ** additional feature **, the function keeps track of multiple 
 * predecessors for a node on (multiple) shortest paths from the source, if they exist.  
 *
 * We will discuss this point in detail in the lecture. The basic idea is,  
 * the array of lists "pred" keeps track of multiple predecessors (if they exist) for 
 * a node on (multiple) shortest paths. Each linked list offers possible predecessors for a node.  
 *  
 * In the following example, while discovering shortest paths from source node '0', we 
 * discovered that node '1' has two possible predecessors on possible shortest paths. 
 * 
Node 0
  Distance
    0 : X
    1 : 2
    2 : 1
  Preds
    0 : NULL
    1 : [0]->[2]->NULL
    2 : [0]->NULL

Node 1
  Distance
    0 : 2
    1 : X
    2 : 3
  Preds
    0 : [1]->NULL
    1 : NULL
    2 : [0]->NULL

Node 2
  Distance
    0 : 3
    1 : 1
    2 : X
  Preds
    0 : [1]->NULL
    1 : [2]->NULL
    2 : NULL

 * 
 * 
 * The function returns 'ShortestPaths' structure with the required information
 * (i.e. 'distance' array, 'predecessor' arrays, source and no_of_nodes in the graph)
 */
ShortestPaths dijkstra(Graph, Vertex);



/**
* The following  "showShortestPaths" functions is defined for you to be able 
* to print out your output and write your own tests. 
* You can choose a suitable implemention (output format) for the following 
* "showShortestPaths" function. 
* 
* Note that we will *not* use your implementation of "showShortestPaths" function
* for our own testing.

* Again, our tests will not use your show function, it's there for your use.
* 
* */
void  showShortestPaths(ShortestPaths);

void  freeShortestPaths(ShortestPaths);