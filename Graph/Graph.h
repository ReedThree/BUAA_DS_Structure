#ifndef __GRAPH_H
#define __GRAPH_H

#define DOT_NODE_FORMAT_BUFFER_LEN 255

#include <stdbool.h>
#include <stddef.h>

typedef int VertexData;

struct GraphEdgeNode {
    int weight;
    size_t otherVertex;
    struct GraphEdgeNode *next;
};

struct GraphVertex {
    VertexData data;
    struct GraphEdgeNode *edgeList;
    size_t edgeCount;
    bool valid;
};

struct Graph {
    struct GraphVertex *vertexList;
    size_t vertexCount;
    size_t vertexCapacity;
};

// First, list of Vertex Data
// Then, list of (edgeData vertexA vertexB)
struct Graph *Graph_create(size_t maxVertexCount);
struct Graph *Graph_fromPattern(size_t vertexCount, size_t edgeCount);
size_t Graph_insertVertex(struct Graph *graph, VertexData data);
void Graph_insertEdge(struct Graph *graph, size_t vertexA, size_t vertexB,
                      int weight);
void Graph_deleteVertex(struct Graph *graph, size_t vertexId);
void Graph_destroyGraph(struct Graph *graph);
void Graph_DFS(struct Graph *graph, size_t beginNode,
               void (*f)(struct GraphVertex *));
void Graph_BFS(struct Graph *graph, size_t beginNode,
               void (*f)(struct GraphVertex *));

void *Graph_adjacentMatrix(struct Graph *graph);
void *Graph_weightMatrix(struct Graph *graph);
void Graph_generateDotGraph(struct Graph *graph, char *outputBuffer);

struct Graph *Graph_MSTPrim(struct Graph *graph, size_t beginVertex);

#endif
