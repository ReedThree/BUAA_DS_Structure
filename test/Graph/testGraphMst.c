#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void f(struct GraphVertex *vertex);

int main(void) {
    size_t vertexCount, edgeCount;
    vertexCount = edgeCount = 0;
    scanf("%zu%zu", &vertexCount, &edgeCount);

    struct Graph *graph = Graph_fromPattern(vertexCount, edgeCount);

    char dotGraphBuffer[2048] = {0};
    Graph_generateDotGraph(graph, dotGraphBuffer);
    printf("1: \n%s\n", dotGraphBuffer);

    struct Graph *mst = Graph_MSTPrim(graph, 0);

    Graph_generateDotGraph(mst, dotGraphBuffer);
    printf("2: \n%s\n", dotGraphBuffer);

    Graph_destroyGraph(graph);
    Graph_destroyGraph(mst);
    return 0;
}

void f(struct GraphVertex *vertex) { printf("%d ", vertex->data); }
