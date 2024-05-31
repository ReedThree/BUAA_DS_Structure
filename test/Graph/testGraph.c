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
    printf("1: ");
    Graph_DFS(graph, 0, f);
    putchar('\n');

    printf("2: ");
    Graph_BFS(graph, 0, f);
    putchar('\n');

    printf("3: \n");
    size_t N = graph->vertexCount;

    bool(*adjacentMatrix)[N] = (bool(*)[N])Graph_adjacentMatrix(graph);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < (N - 1); j++) {
            printf("%d ", adjacentMatrix[i][j]);
        }
        printf("%d\n", adjacentMatrix[i][N - 1]);
    }

    char dotBuffer[1024] = {0};
    Graph_generateDotGraph(graph, dotBuffer);
    printf("4: \n%s\n", dotBuffer);

    free(adjacentMatrix);
    Graph_destroyGraph(graph);
    return 0;
}

void f(struct GraphVertex *vertex) { printf("%d ", vertex->data); }
