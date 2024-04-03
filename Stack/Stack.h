#ifndef __STACK_H
#define __STACK_H

#include <stddef.h>
#include <stdbool.h>

#define ARRAY_DEFAULT_CAPACITY 10
#define ARRAY_RESIZE_FACTOR 2

struct Stack_Data {
    int n;
};

void Stack_destroyData(struct Stack_Data *target);

struct Stack {
    struct Stack_Data **lst;
    size_t currentSize;
    size_t capacity;
    size_t maxSize;
};

// set maxSize to zero for an "infinity" size
struct Stack *Stack_createStack(size_t maxSize);
void Stack_destroyStack(struct Stack *target);
bool Stack_push(struct Stack *s, struct Stack_Data *element);
struct Stack_Data *Stack_pop(struct Stack *s);
bool Stack_isEmpty(struct Stack *s);
bool Stack_isFull(struct Stack *s);
struct Stack_Data *Stack_getTop(struct Stack *s);

#endif
