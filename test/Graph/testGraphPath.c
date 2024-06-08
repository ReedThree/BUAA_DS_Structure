#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t vertexCount, edgeCount;
    vertexCount = edgeCount = 0;
    scanf("%zu%zu", &vertexCount, &edgeCount);
    struct Graph *graph = Graph_fromPattern(vertexCount, edgeCount);

    char dotBuffer[2048] = {0};
    Graph_generateDotGraph(graph, dotBuffer);
    printf("1:\n%s\n", dotBuffer);

    size_t *minPathViaVertex = Graph_Dijkstra(graph, 0);
    printf("2:\n");
    for (size_t i = 0; i < graph->vertexCount; i++) {
        VertexData data = graph->vertexList[i].data;
        printf("%d ", data);
    }
    putchar('\n');
    for (size_t i = 0; i < graph->vertexCount; i++) {
        VertexData data = graph->vertexList[minPathViaVertex[i]].data;
        printf("%d ", data);
    }
    putchar('\n');

    free(minPathViaVertex);
    Graph_destroyGraph(graph);
    return 0;
}