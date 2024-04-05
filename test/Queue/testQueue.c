#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

void Queue_destroyData(struct Queue_Data *target) { free(target); }

int main(void) {
    struct Queue_Data d1 = {1};
    struct Queue_Data d2 = {2};
    struct Queue_Data d3 = {3};
    struct Queue_Data d4 = {4};
    struct Queue_Data d5 = {5};
    struct Queue_Data d6 = {6};

    struct Queue *queue = Queue_createQueue((unsigned)5);

    if (Queue_isFull(queue) == false) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Queue_isEmpty(queue) == true) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Queue_getHead(queue) == NULL) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    Queue_enQueue(queue, &d1);
    Queue_enQueue(queue, &d2);
    Queue_enQueue(queue, &d3);
    Queue_enQueue(queue, &d4);
    Queue_enQueue(queue, &d5);

    printf("%zu\n", queue->count);

    if (Queue_getHead(queue)->n == d1.n) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Queue_isFull(queue) == true) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Queue_isEmpty(queue) == false) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Queue_enQueue(queue, &d6) == false) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }
    size_t count = queue->count;
    for (size_t i = 0; i < count; i++) {
        struct Queue_Data *ret = Queue_deQueue(queue);
        printf("%d\n", ret->n);
        Queue_destroyData(ret);
    }

    if (Queue_isFull(queue) == false) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Queue_isEmpty(queue) == true) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    Queue_destroyQueue(queue);

    return 0;
}
