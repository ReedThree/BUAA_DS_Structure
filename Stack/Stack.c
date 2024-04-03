#include "Stack.h"
#include <stdlib.h>
#include <string.h>

struct Stack *Stack_createStack(size_t maxSize) {
    struct Stack *result = (struct Stack *)malloc(sizeof(struct Stack));
    if (maxSize > 0) {
        result->lst =
            (struct Stack_Data **)malloc(maxSize * sizeof(struct Stack *));
        result->capacity = maxSize;
    } else {
        result->lst = (struct Stack_Data **)malloc(ARRAY_DEFAULT_CAPACITY *
                                                   sizeof(struct Stack *));
        result->capacity = ARRAY_DEFAULT_CAPACITY;
    }
    result->currentSize = 0;
    result->maxSize = maxSize;

    return result;
}

void Stack_destroyStack(struct Stack *target) {
    for (size_t i = 0; i < target->currentSize; i++) {
        Stack_destroyData(target->lst[i]);
    }
    free(target->lst);
    free(target);
}

bool Stack_push(struct Stack *s, struct Stack_Data *element) {
    struct Stack_Data *_element =
        (struct Stack_Data *)malloc(sizeof(struct Stack_Data));
    memcpy(_element, element, sizeof(struct Stack_Data));
    if (s->currentSize < s->capacity) {
        s->lst[s->currentSize] = _element;
        s->currentSize++;
        return true;
    } else {
        if (s->maxSize > 0) {
            free(_element);
            return false;
        } else {
            s->capacity *= ARRAY_RESIZE_FACTOR;
            s->lst = realloc(s->lst, s->capacity * sizeof(struct Stack_Data *));
            s->lst[s->currentSize] = _element;
            s->currentSize++;
            return true;
        }
    }
}
struct Stack_Data *Stack_pop(struct Stack *s) {
    if (s->currentSize == 0) {
        return NULL;
    }

    struct Stack_Data *ret = s->lst[s->currentSize - 1];
    s->currentSize--;
    return ret;
}
bool Stack_isEmpty(struct Stack *s) { return (bool)(s->currentSize == 0); }
bool Stack_isFull(struct Stack *s) {
    if (s->maxSize == 0) {
        return false;
    } else {
        return (bool)(s->currentSize == s->maxSize);
    }
}
struct Stack_Data *Stack_getTop(struct Stack *s) {
    if (s->currentSize == 0) {
        return NULL;
    }
    return s->lst[s->currentSize - 1];
}
