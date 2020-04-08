#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

#include "PQ.h"
#include "CentralityMeasures.h"
#include "Dijkstra.h"

//static int numOfAdjacent (Graph g,Vertex v);
static int reachableNode(Graph g, Vertex v);

NodeValues outDegreeCentrality(Graph g) {
    NodeValues outDegree;
    outDegree.noNodes = numVerticies(g) - 1;
    outDegree.values = malloc(sizeof(double) * numVerticies(g));
    
    for(int i = 0; i <numVerticies(g); i++) {
        AdjList out = outIncident(g,i);
        AdjList curr = out;
        double tmp = 0;
        
        while(curr != NULL) {
            tmp++;
            curr = curr->next;
        }
        outDegree.values[i] = tmp;
    }
    
    return outDegree;
}

NodeValues inDegreeCentrality(Graph g) {
    NodeValues inDegree;
    inDegree.noNodes = numVerticies(g) - 1;
    inDegree.values = malloc(sizeof(double) * numVerticies(g));
    for(int i = 0; i < numVerticies(g); i++) {
        AdjList in = inIncident(g,i);
        AdjList curr = in;
        double tmp = 0;
        
        while(curr != NULL) {
            tmp++;
            curr = curr->next;
        }
        inDegree.values[i] = tmp;
    }
    
    return inDegree;
    
    
}

// for undirected graph
NodeValues degreeCentrality(Graph g) {
    NodeValues v;
    v.noNodes = numVerticies(g) - 1;
    v.values = malloc(sizeof(double) * numVerticies(g));
    
    
    NodeValues out = outDegreeCentrality(g);
    NodeValues in = inDegreeCentrality(g);
    
    for(int i = 0; i < numVerticies(g); i++) {
        v.values[i] = out.values[i] + in.values[i];
    }
    
    return v;
}

NodeValues closenessCentrality(Graph g){
    
    NodeValues closeness;
    closeness.noNodes = numVerticies(g) - 1;
    closeness.values = malloc(sizeof(double) * numVerticies(g));
    ShortestPaths s;
    for(int i = 0; i < numVerticies(g); i++) {
        
        s = dijkstra(g,i);
        double sumOfPaths = 0.0;
        int n = reachableNode(g,i);
        for(int j = 0; j < numVerticies(g);j++) {
            sumOfPaths = sumOfPaths + s.dist[j];
        }
        closeness.values[i] = ((n-1)/(numVerticies(g))) * ((n-1)/sumOfPaths);
    }
    return closeness;
}


NodeValues betweennessCentrality(Graph g){
    NodeValues throwAway = {0};
     return throwAway;
    
}
NodeValues betweennessCentralityNormalised(Graph g){
    assert(numVerticies(g) > 2);
    
    NodeValues throwAway = {0};
     return throwAway;
}



void  showNodeValues(NodeValues n) {
    for (int i = 0; i <= n.noNodes; i++) {
        printf("%d: %.6lf\n", i, n.values[i]);
    }
}
void  freeNodeValues(NodeValues v) {
    free(v.values);
}


//count the number of linked node of a given vertex
/*static int numOfAdjacent (Graph g,Vertex v) {
    int num = 0;
    for(int i = 0; i < numVerticies(g); i++) {
        if(adjacent(g,v,i)) {
            num++;
        }
    }
    return num;
}*/

static int reachableNode(Graph g, Vertex v) {
    int count = 0;;
    AdjList out = outIncident(g,v);
    AdjList node = out;
    
    int visited[999];
    for(int i = 0;i < numVerticies(g);i++) {
        visited[i] = 0;
    }

    while(node != NULL) {
        if(visited[node->w] == 0) {
            visited[node->w] == 1;
            count++;
        }
        node = node->next;
    }

    for(int i = 0;i < numVerticies(g);i++) {
        if(visited[i] == 1) {
            out = outIncident(g,i);
            for(node = out;node != NULL;node = node->next) {
                if(visited[node->w] == 0) {
                visited[node->w] == 1;
                count++;
                }
            }
        }
    }
    return count;
}