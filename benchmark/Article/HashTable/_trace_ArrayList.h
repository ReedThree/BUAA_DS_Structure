#ifndef __TRACE_ARRAY_LIST_H
#define __TRACE_ARRAY_LIST_H
#include <stdio.h>
#include <stdlib.h>

#define RESIZE_FACTOR 2

// imply by user
struct _trace_Data {
    void *addr;
    size_t size;
};
void _trace_destroyData(struct _trace_Data *target);
void _trace_printData(struct _trace_Data *target);
int _trace_dataEquals(struct _trace_Data *a, struct _trace_Data *b);
int _trace_dataCmp(const void *a, const void *b);
// ----

struct _trace_ArrayList {
    struct _trace_Data **lst;
    int capacity;
    int len;
};

struct _trace_ArrayList *_trace_createList(int capacity);
void _trace_destroyList(struct _trace_ArrayList *target);
void _trace_printList(struct _trace_ArrayList *target);
struct _trace_Data *_trace_listGetByPos(struct _trace_ArrayList *lst, int pos);
struct _trace_Data *_trace_listSearch(struct _trace_ArrayList *lst, struct _trace_Data data);
struct _trace_Data *_trace_listSearchOrdered(struct _trace_ArrayList *lst, struct _trace_Data *data);
int _trace_listGetPos(struct _trace_ArrayList *lst, struct _trace_Data *data);
int _trace_listGetPosOrdered(struct _trace_ArrayList *lst, struct _trace_Data *data);
int _trace_listInsertItem(struct _trace_ArrayList *lst, int pos, struct _trace_Data data);
void _trace_listInsertItemOrdered(struct _trace_ArrayList *lst, struct _trace_Data data);
int _trace_listDeleteItem(struct _trace_ArrayList *lst, int pos);
void _trace_listSort(struct _trace_ArrayList *lst, __compar_fn_t compar);

#endif