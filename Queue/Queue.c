#include "Queue.h"
#include <stdlib.h>
#include <string.h>

struct Queue *Queue_createQueue(size_t capacity) {
    struct Queue *result = (struct Queue *)malloc(sizeof(struct Queue));
    result->lst =
        (struct Queue_Data **)malloc(capacity * sizeof(struct Queue_Data *));
    for (size_t i = 0; i < capacity; i++) {
        result->lst[i] = NULL;
    }
    result->capacity = capacity;
    result->front = 0;
    result->rear = capacity - 1;
    result->count = 0;
    return result;
}
void Queue_destroyQueue(struct Queue *target) {
    for (size_t i = 0; i < target->capacity; i++) {
        if (target->lst[i] != NULL) {
            Queue_destroyData(target->lst[i]);
        }
    }
    free(target->lst);
    free(target);
}
bool Queue_enQueue(struct Queue *q, struct Queue_Data *element) {
    if (Queue_isFull(q)) {
        return false;
    }
    struct Queue_Data *_element =
        (struct Queue_Data *)malloc(sizeof(struct Queue_Data));
    memcpy(_element, element, sizeof(struct Queue_Data));

    q->rear = (q->rear + 1) % q->capacity;
    q->lst[q->rear] = _element;
    q->count++;

    return true;
}
struct Queue_Data *Queue_deQueue(struct Queue *q) {
    if (Queue_isEmpty(q)) {
        return NULL;
    }
    struct Queue_Data *ret = q->lst[q->front];
    q->lst[q->front] = NULL;
    q->front = (q->front + 1) % q->capacity;
    q->count--;
    return ret;
}
bool Queue_isFull(struct Queue *q) { return (bool)(q->count == q->capacity); }
bool Queue_isEmpty(struct Queue *q) { return (bool)(q->count == 0); }
