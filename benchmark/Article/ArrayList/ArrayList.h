#ifndef __H_ARRAY_LIST
#define __H_ARRAY_LIST
#include <stdio.h>
#include <stdlib.h>

#define RESIZE_FACTOR 8

// imply by user
struct Data {
    char *word;
    int count;
};
void destroyData(struct Data *target);
void printData(struct Data *target);
int dataEquals(struct Data *a, struct Data *b);
int dataCmp(const void *a, const void *b);
// ----
struct ArrayList {
    struct Data **lst;
    int capacity;
    int len;
};

struct ArrayList *createList(int capacity);
void destroyList(struct ArrayList *target);
void printList(struct ArrayList *target);
struct Data *listGetByPos(struct ArrayList *lst, int pos);
struct Data *listSearch(struct ArrayList *lst, struct Data data);
struct Data *listSearchOrdered(struct ArrayList *lst, struct Data *data);
int listInsertItem(struct ArrayList *lst, int pos, struct Data data);
void listInsertItemOrdered(struct ArrayList *lst, struct Data data);
int listDeleteItem(struct ArrayList *lst, int pos);
void listSort(struct ArrayList *lst, __compar_fn_t compar);

void *_malloc(size_t __size);
void _free(void *__ptr);
void *_realloc(void *__ptr, size_t __size);

#endif