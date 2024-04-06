#include "DoubleLinkedList.h"
#include "trace.h"
#include <stdio.h>

void f(struct DoubleLinkedList_Node *a);

int main(void) {
    traceInit();
    struct DoubleLinkedList_Data d1 = {5, 1};
    struct DoubleLinkedList_Data d2 = {4, 2};
    struct DoubleLinkedList_Data d3 = {3, 3};
    struct DoubleLinkedList_Data d4 = {2, 4};
    struct DoubleLinkedList_Data d5 = {1, 5};

    struct DoubleLinkedList *lst = DoubleLinkedList_createList(&d1);

    DoubleLinkedList_insertOrdered(lst, &d5);
    DoubleLinkedList_insertOrdered(lst, &d4);
    DoubleLinkedList_insertOrdered(lst, &d3);
    DoubleLinkedList_insertOrdered(lst, &d2);

    struct DoubleLinkedList_Data d8 = {-2, 8};
    struct DoubleLinkedList_Data d9 = {-3, 9};

    DoubleLinkedList_push(lst, &d8);
    DoubleLinkedList_push(lst, &d9);

    printf("Len = %zu\n", DoubleLinkedList_getLength(lst));
    DoubleLinkedList_printLst(lst);
    DoubleLinkedList_printLstReversed(lst);
    struct DoubleLinkedList_Data *p1 = DoubleLinkedList_pop(lst);
    DoubleLinkedList_printData(p1);
    putchar('\n');
    struct DoubleLinkedList_Data *p2 = DoubleLinkedList_pop(lst);
    DoubleLinkedList_printData(p2);
    putchar('\n');

    printf("Len = %zu\n", DoubleLinkedList_getLength(lst));
    DoubleLinkedList_printLst(lst);

    DoubleLinkedList_destroyList(lst);
    _free(p1);
    _free(p2);
    traceSummarize();
    traceFree();
    return 0;
}

void DoubleLinkedList_destroyData(struct DoubleLinkedList_Data *target) {
    _free(target);
}
void DoubleLinkedList_printData(struct DoubleLinkedList_Data *data) {
    printf("{c = %d, p = %d}", data->c, data->p);
}
int DoubleLinkedList_dataEquals(struct DoubleLinkedList_Data *a,
                                struct DoubleLinkedList_Data *b) {
    if (a->p == b->p) {
        return 1;
    } else {
        return 0;
    }
}
int DoubleLinkedList_dataCmp(struct DoubleLinkedList_Data *a,
                             struct DoubleLinkedList_Data *b) {
    if (a->p < b->p) {
        return -1;
    } else if (a->p > b->p) {
        return 1;
    } else {
        return 0;
    }
}

void f(struct DoubleLinkedList_Node *a) { printf("%d", a->d->p); }
