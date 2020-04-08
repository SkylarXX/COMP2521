#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "Graph.h"


typedef struct GraphRep {
    int    nV;    // #vertices
    int    nE;    // #edges
    adjListNode  **edges;
} GraphRep;

static int validV(Graph g, Vertex v);
static int inList(Graph g, Vertex src,Vertex dest);
static AdjList insertList(AdjList head, Vertex w, int weight);
static AdjList deleteList(AdjList head,Vertex w);

Graph newGraph(int noNodes) {
    
    assert(noNodes >= 0 );
    int i;
    
    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = noNodes;
    g->nE = 0;
    
    g->edges = malloc(noNodes * sizeof(adjListNode *));
    assert(g->edges != NULL);
    for(i = 0; i < noNodes; i++)
        g->edges[i] = NULL;
    
    return g;
    
}

static int validV(Graph g, Vertex v) {
    return (g != NULL && v >= 0 && v < g->nV);
}


void  insertEdge(Graph g, Vertex src, Vertex dest, int weight){
    assert(g != NULL && validV(g,dest));
    if(!inList(g,src,dest)) {
        g->edges[src] = insertList(g->edges[src],dest,weight);
        //insertList(g->edges[dest],src,weight);
        g->nE ++;
    }
    
}


void  removeEdge(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL && validV(g, dest));
    
    if(inList(g,src,dest)) {
        g->edges[src] = deleteList(g->edges[src],dest);
        //deleteList(g,dest,src);
        g->nE --;
    }
    
}

bool  adjacent(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL && validV(g, src) && validV(g, dest));
    
    return inList(g,src,dest);
}

int  numVerticies(Graph g) {
    return g->nV;
}

AdjList outIncident(Graph g, Vertex v) {
    AdjList node = g->edges[v];
    return node;
    
}

AdjList inIncident(Graph g, Vertex v) {
    int i;
    AdjList list = malloc(sizeof(struct _adjListNode));
    list = NULL;
    
    for(i = 0;i < g->nV; i++) {
        if(inList(g,i,v)) {
            for(AdjList node=g->edges[i]; node!= NULL; node = node->next){
                if(node->w == v) {
                    list = insertList(list,i,node->weight);
                }
            }
        }
    }
    return list;
}

void  showGraph(Graph g) {
    for(int i = 0; i < g->nV; i++) {
        AdjList n = g->edges[i];
        printf("\n Adjacency list of vertex %d\n head", i);
        while(n) {
            printf("-> %d", n->w);
            n = n->next;
        }
        printf("\n");
    }
    
}

void  freeGraph(Graph g) {
    if(g == NULL)
        return;
    for(int i = 0;i < g->nV;i++) {
        AdjList tmp;
        while(g->edges[i]!= NULL) {
            tmp = g->edges[i];
            g->edges[i] = g->edges[i]->next;
            free(tmp);
        }
        free(g->edges[i]);
    }
    
}

static int inList(Graph g, Vertex src,Vertex dest) {
    
    AdjList node = g->edges[src];
    while(node != NULL) {
        if(node->w == dest) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

//insert to the head of the list
static AdjList insertList(AdjList head, Vertex w, int weight) {
    
    AdjList new = malloc(sizeof(struct _adjListNode));
    new->w = w;
    new->weight = weight;
    new->next = head;
    
    return new;
}

static AdjList deleteList(AdjList head,Vertex w) {
    
    assert(head != NULL);
    
    AdjList temp = head;
    AdjList prev = temp;
    
    if(temp != NULL && temp->w == w) {
        head = temp->next;
        free(temp);
    }

    while(temp != NULL && temp->w != w) {
        prev = temp;
        temp = temp->next;
    }
    //temp->w == w
    prev->next = temp->next;
    
    
    return head;
}
