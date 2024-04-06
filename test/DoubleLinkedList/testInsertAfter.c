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

    DoubleLinkedList_insertIndex(lst, 0, &d2);
    DoubleLinkedList_insertIndex(lst, 0, &d3);
    DoubleLinkedList_insertIndex(lst, 0, &d4);
    DoubleLinkedList_insertIndex(lst, 0, &d5);

    struct DoubleLinkedList_Data d6 = {0, 6};

    DoubleLinkedList_insertAfter(lst, lst->head, &d6);
    DoubleLinkedList_insertAfter(lst, lst->tail, &d6);

    printf("Len = %zu\n", DoubleLinkedList_getLength(lst));
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
