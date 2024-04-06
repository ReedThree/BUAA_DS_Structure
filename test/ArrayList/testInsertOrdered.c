#include "ArrayList.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    traceInit();
    struct ArrayList_Data d1 = {"1", 5};
    struct ArrayList_Data d2 = {"2", 4};
    struct ArrayList_Data d3 = {"3", 3};
    struct ArrayList_Data d4 = {"4", 2};
    struct ArrayList_Data d5 = {"5", 1};
    struct ArrayList *lst = ArrayList_createList(2);

    ArrayList_insertItemOrdered(lst, &d5);
    ArrayList_insertItemOrdered(lst, &d4);
    ArrayList_insertItemOrdered(lst, &d3);
    ArrayList_insertItemOrdered(lst, &d2);
    ArrayList_insertItemOrdered(lst, &d1);

    printf("Len = %zu\n", ArrayList_getLength(lst));
    ArrayList_printList(lst);

    ArrayList_destroyList(lst);
    traceSummarize();
    traceFree();
    return 0;
}

void ArrayList_destroyData(struct ArrayList_Data *target) { _free(target); }
void ArrayList_printData(struct ArrayList_Data *target) {
    printf("{word = \"%s\", count = %d}", target->word, target->count);
}
int ArrayList_dataEquals(struct ArrayList_Data *a, struct ArrayList_Data *b) {
    if (strcmp(a->word, b->word) == 0) {
        return 1;
    } else {
        return 0;
    }
}
int ArrayList_dataCmp(const void *a, const void *b) {
    struct ArrayList_Data *dA = *((struct ArrayList_Data **)a);
    struct ArrayList_Data *dB = *((struct ArrayList_Data **)b);
    return strcmp(dA->word, dB->word);
}
