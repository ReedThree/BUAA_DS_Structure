#include "DoubleLinkedList.h"
#include "trace.h"
#include <stdio.h>

void f(struct DoubleLinkedList_Node *a);

int main() {
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

    DoubleLinkedList_insertIndexReversed(lst, 0, &d3);
    struct DoubleLinkedList_Node *n = DoubleLinkedList_getByIndex(lst, 3);
    DoubleLinkedList_deleteNode(lst, n);
    DoubleLinkedList_deleteIndex(lst, 0);
    DoubleLinkedList_deleteIndexReversed(lst, 0);
    printf("Len = %d\n", DoubleLinkedList_getLength(lst));
    DoubleLinkedList_printLst(lst);
    DoubleLinkedList_printLstReversed(lst);

    DoubleLinkedList_destroyList(lst);
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