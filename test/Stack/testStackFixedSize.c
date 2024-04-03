#include "Stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void Stack_destroyData(struct Stack_Data *target) { free(target); }

int main(void) {
    struct Stack_Data d1 = {1};
    struct Stack_Data d2 = {2};
    struct Stack_Data d3 = {3};
    struct Stack_Data d4 = {4};
    struct Stack_Data d5 = {5};
    struct Stack_Data d6 = {6};

    struct Stack *stack = Stack_createStack((unsigned)5);

    if (Stack_isEmpty(stack) == true) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Stack_getTop(stack) == NULL) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    Stack_push(stack, &d1);
    Stack_push(stack, &d2);
    Stack_push(stack, &d3);
    Stack_push(stack, &d4);
    Stack_push(stack, &d5);

    if (Stack_isEmpty(stack) == false) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    printf("%zu\n", stack->currentSize);

    for (int i = 0; i < 5; i++) {
        struct Stack_Data *ret = Stack_pop(stack);
        printf("%d ", ret->n);
        Stack_destroyData(ret);
    }
    putchar('\n');
    printf("%zu\n", stack->currentSize);

    if (Stack_pop(stack) == NULL) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    Stack_push(stack, &d1);
    Stack_push(stack, &d2);
    Stack_push(stack, &d3);
    Stack_push(stack, &d4);
    Stack_push(stack, &d5);

    if (Stack_push(stack, &d6) == false) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    if (Stack_isFull(stack) == true) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }

    struct Stack_Data *ret = Stack_getTop(stack);
    if (ret->n == d5.n) {
        printf("Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }
    Stack_destroyStack(stack);

    return 0;
}
