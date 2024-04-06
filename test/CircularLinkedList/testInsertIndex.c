#include "CircularLinkedList.h"
#include "trace.h"
#include <stdio.h>
/*

*/
int main(void) {
    traceInit();
    struct CircularLinkedList_Data d1 = {5, 1};
    struct CircularLinkedList_Data d2 = {4, 2};
    struct CircularLinkedList_Data d3 = {3, 3};
    struct CircularLinkedList_Data d4 = {2, 4};
    struct CircularLinkedList_Data d5 = {1, 5};
    struct CircularLinkedList *lst = CircularLinkedList_createList(&d1);
    //    insertIndex(lst, 0, d1);
    CircularLinkedList_insertIndex(lst, 0, &d2);
    CircularLinkedList_insertIndex(lst, 0, &d3);
    CircularLinkedList_insertIndex(lst, 0, &d4);
    CircularLinkedList_insertIndex(lst, 0, &d5);
    CircularLinkedList_insertIndex(lst, 5, &d5);
    printf("Len = %zu\n", CircularLinkedList_getLength(lst));
    CircularLinkedList_printLst(lst);

    CircularLinkedList_destroyList(lst);
    traceSummarize();
    traceFree();
    return 0;
}

void CircularLinkedList_printData(struct CircularLinkedList_Data *data) {
    printf("{c = %d, p = %d}", data->c, data->p);
}
int CircularLinkedList_dataEquals(struct CircularLinkedList_Data *a,
                                  struct CircularLinkedList_Data *b) {
    if (a->p == b->p) {
        return 1;
    } else {
        return 0;
    }
}
int CircularLinkedList_dataCmp(struct CircularLinkedList_Data *a,
                               struct CircularLinkedList_Data *b) {
    if (a->p < b->p) {
        return -1;
    } else if (a->p > b->p) {
        return 1;
    } else {
        return 0;
    }
}
void CircularLinkedList_destroyData(struct CircularLinkedList_Data *target) {
    _free(target);
}
