#include "Graph.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Graph *Graph_create(size_t maxVertexCount) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertexCount = 0;

    struct GraphVertex *vertexList = (struct GraphVertex *)malloc(
        maxVertexCount * sizeof(struct GraphVertex));
    graph->vertexList = vertexList;
    return graph;
}

struct Graph *Graph_fromPattern(size_t vertexCount, size_t edgeCount) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertexCount = vertexCount;
    graph->vertexCapacity = vertexCount;

    struct GraphVertex *vertexList =
        (struct GraphVertex *)malloc(vertexCount * sizeof(struct GraphVertex));
    graph->vertexList = vertexList;

    for (size_t i = 0; i < vertexCount; i++) {
        scanf("%d", &(graph->vertexList[i].data));
        graph->vertexList[i].edgeCount = 0;
        graph->vertexList[i].edgeList = NULL;
    }

    for (size_t i = 0; i < edgeCount; i++) {
        int d;
        scanf("%d", &d);

        size_t vertexA, vertexB;
        vertexA = vertexB = 0;
        scanf("%zu%zu", &vertexA, &vertexB);

        Graph_insertEdge(graph, vertexA, vertexB, d);
    }

    return graph;
}

size_t Graph_insertVertex(struct Graph *graph, VertexData data) {
    size_t vertexId = graph->vertexCount;

    graph->vertexList[vertexId].data = data;
    graph->vertexList[vertexId].edgeList = NULL;
    graph->vertexList[vertexId].edgeCount = 0;

    graph->vertexCount++;
    return vertexId;
}

void Graph_insertEdge(struct Graph *graph, size_t vertexA, size_t vertexB,
                      int weight) {
    struct GraphEdgeNode *node =
        (struct GraphEdgeNode *)malloc(sizeof(struct GraphEdgeNode));

    node->weight = weight;
    node->otherVertex = vertexB;

    if (graph->vertexList[vertexA].edgeCount == 0) {
        graph->vertexList[vertexA].edgeList = node;
        node->next = NULL;
    } else {
        node->next = graph->vertexList[vertexA].edgeList;
        graph->vertexList[vertexA].edgeList = node;
    }

    graph->vertexList[vertexA].edgeCount++;

    struct GraphEdgeNode *otherNode =
        (struct GraphEdgeNode *)malloc(sizeof(struct GraphEdgeNode));

    otherNode->weight = weight;
    otherNode->otherVertex = vertexA;

    if (graph->vertexList[vertexB].edgeCount == 0) {

        graph->vertexList[vertexB].edgeList = otherNode;
        otherNode->next = NULL;
    } else {
        otherNode->next = graph->vertexList[vertexB].edgeList;
        graph->vertexList[vertexB].edgeList = otherNode;
    }

    graph->vertexList[vertexB].edgeCount++;
}

void Graph_destroyGraph(struct Graph *graph) {
    for (size_t i = 0; i < graph->vertexCount; i++) {
        struct GraphEdgeNode *current = graph->vertexList[i].edgeList;

        while (current != NULL) {
            struct GraphEdgeNode *next = current->next;

            free(current);
            current = next;
        }
    }
    free(graph->vertexList);
    free(graph);
}

void Graph_DFS(struct Graph *graph, size_t beginNode,
               void (*f)(struct GraphVertex *)) {
    bool *visited = (bool *)calloc(graph->vertexCount, sizeof(bool));

    size_t *nodeStack = (size_t *)malloc(graph->vertexCount * sizeof(size_t));
    size_t nodeStackTop = 0;

    visited[beginNode] = true;
    nodeStack[nodeStackTop] = beginNode;
    nodeStackTop++;

    while (nodeStackTop > 0) {
        size_t topNodeId = nodeStack[nodeStackTop - 1];
        nodeStackTop--;

        f(&graph->vertexList[topNodeId]);

        struct GraphEdgeNode *current = graph->vertexList[topNodeId].edgeList;
        while (current != NULL) {
            size_t otherNodeId = current->otherVertex;
            if (!visited[otherNodeId]) {
                visited[otherNodeId] = true;
                nodeStack[nodeStackTop] = otherNodeId;
                nodeStackTop++;
            }
            current = current->next;
        }
    }

    free(visited);
    free(nodeStack);
}
void Graph_BFS(struct Graph *graph, size_t beginNode,
               void (*f)(struct GraphVertex *)) {
    bool *visited = (bool *)calloc(graph->vertexCount, sizeof(bool));
    size_t *nodeQueue = (size_t *)malloc(graph->vertexCount * sizeof(size_t));
    size_t nodeQueueCapacity = graph->vertexCount;
    size_t nodeQueueLen = 0;
    size_t nodeQueueFront = 0;
    size_t nodeQueueRear = nodeQueueCapacity - 1;

    visited[beginNode] = true;
    nodeQueueRear = (nodeQueueRear + 1) % nodeQueueCapacity;
    nodeQueue[nodeQueueRear] = beginNode;
    nodeQueueLen++;

    while (nodeQueueLen > 0) {
        size_t currentNodeId = nodeQueue[nodeQueueFront];
        nodeQueueFront = (nodeQueueFront + 1) % nodeQueueCapacity;
        nodeQueueLen--;

        f(&graph->vertexList[currentNodeId]);

        struct GraphEdgeNode *current =
            graph->vertexList[currentNodeId].edgeList;
        while (current != NULL) {
            size_t otherNodeId = current->otherVertex;
            if (!visited[otherNodeId]) {
                visited[otherNodeId] = true;

                nodeQueueRear = (nodeQueueRear + 1) % nodeQueueCapacity;
                nodeQueue[nodeQueueRear] = otherNodeId;
                nodeQueueLen++;
            }
            current = current->next;
        }
    }

    free(visited);
    free(nodeQueue);
}

void *Graph_adjacentMatrix(struct Graph *graph) {
    size_t N = graph->vertexCount;

    bool(*adjacentMatrix)[N] = (bool(*)[N])calloc(N * N, sizeof(bool));

    for (size_t i = 0; i < graph->vertexCount; i++) {
        struct GraphEdgeNode *current = graph->vertexList[i].edgeList;

        while (current != NULL) {
            adjacentMatrix[i][current->otherVertex] = true;
            current = current->next;
        }
    }

    return (void *)adjacentMatrix;
}

void *Graph_weightMatrix(struct Graph *graph) {
    size_t N = graph->vertexCount;

    int(*weightMatrix)[N] = (int(*)[N])malloc(N * N * sizeof(int));
    for (size_t i = 0; i < graph->vertexCount; i++) {
        for (size_t j = 0; j < graph->vertexCount; j++) {
            weightMatrix[i][j] = INT_MAX;
        }
    }

    for (size_t i = 0; i < graph->vertexCount; i++) {
        weightMatrix[i][i] = 0;
    }

    for (size_t i = 0; i < graph->vertexCount; i++) {
        struct GraphEdgeNode *current = graph->vertexList[i].edgeList;

        while (current != NULL) {
            weightMatrix[i][current->otherVertex] = current->weight;
            current = current->next;
        }
    }

    return (void *)weightMatrix;
}

void Graph_generateDotGraph(struct Graph *graph, char *outputBuffer) {
    size_t N = graph->vertexCount;
    bool(*visited)[N] = (bool(*)[N])calloc(N * N, sizeof(bool));

    const char *dotBegin = "graph G {\nnode [shape = circle;];\n";
    strcpy(outputBuffer, dotBegin);

    char nodeFormatBuffer[DOT_NODE_FORMAT_BUFFER_LEN] = {0};
    for (size_t i = 0; i < graph->vertexCount; i++) {
        sprintf(nodeFormatBuffer, "%zu [label = \"%d\";];\n", i,
                graph->vertexList[i].data);
        strcat(outputBuffer, nodeFormatBuffer);
    }

    for (size_t i = 0; i < graph->vertexCount; i++) {
        struct GraphEdgeNode *current = graph->vertexList[i].edgeList;

        while (current != NULL) {
            if (!visited[i][current->otherVertex]) {
                sprintf(nodeFormatBuffer, "%zu -- %zu [label = \"%d\";];\n", i,
                        current->otherVertex, current->weight);
                strcat(outputBuffer, nodeFormatBuffer);
                visited[i][current->otherVertex] = true;
                visited[current->otherVertex][i] = true;
            }

            current = current->next;
        }
    }

    strcat(outputBuffer, "}");
    free(visited);
}

struct Graph *Graph_MSTPrim(struct Graph *graph, size_t beginVertex) {
    size_t N = graph->vertexCount;

    int(*weightMatrix)[N] = Graph_weightMatrix(graph);

    int *minweight = (int *)malloc(N * sizeof(int));
    memcpy(minweight, weightMatrix[beginVertex], N * sizeof(int));

    size_t *edges = (size_t *)malloc(N * sizeof(size_t));

    struct Graph *mstGraph = Graph_create(N);

    size_t *toNewId = (size_t *)calloc(N, sizeof(size_t));

    Graph_insertVertex(mstGraph, graph->vertexList[beginVertex].data);
    toNewId[beginVertex] = 0;

    for (size_t i = 0; i < N; i++) {
        edges[i] = beginVertex;
    }

    while (1) {
        int minW = INT_MAX;
        size_t minIndex = 0;

        for (size_t i = 0; i < N; i++) {
            if (minweight[i] != 0) {
                if (minweight[i] < minW) {
                    minW = minweight[i];
                    minIndex = i;
                }
            }
        }

        size_t currentId =
            Graph_insertVertex(mstGraph, graph->vertexList[minIndex].data);
        toNewId[minIndex] = currentId;
        size_t lastId = toNewId[edges[minIndex]];
        Graph_insertEdge(mstGraph, lastId, currentId, minW);

        minweight[minIndex] = 0;
        bool end = true;

        for (size_t i = 0; i < N; i++) {
            if (weightMatrix[minIndex][i] < minweight[i]) {
                minweight[i] = weightMatrix[minIndex][i];
                edges[i] = minIndex;
            }
        }

        for (size_t i = 0; i < N; i++) {
            if (minweight[i] != 0) {
                end = false;
            }
        }

        if (end) {
            break;
        }
    }
    free(weightMatrix);
    free(minweight);
    free(edges);
    free(toNewId);
    return mstGraph;
}
