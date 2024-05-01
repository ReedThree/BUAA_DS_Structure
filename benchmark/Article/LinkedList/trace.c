#include "trace.h"
#include "_trace_ArrayList.h"
#include <stdio.h>
#include <stdlib.h>

size_t total_malloc = 0;
size_t total_free = 0;
size_t max_memory = 0;

struct _trace_ArrayList *store = NULL;

void traceInit() { store = _trace_createList(DEFAULT_STORE_CAPACITY); }

void traceFree() { _trace_destroyList(store); }

void *_malloc(size_t __size) {
    void *addr = malloc(__size);
    struct _trace_Data allocInfo = {addr, __size};
    _trace_listInsertItemOrdered(store, allocInfo);
    total_malloc += __size;
    size_t current_memory = total_malloc - total_free;
    if (current_memory > max_memory) {
        max_memory = current_memory;
    }
    return addr;
}
void _free(void *__ptr) {
    struct _trace_Data target = {__ptr, 0};
    int pos = _trace_listGetPosOrdered(store, &target);
    if (pos == -1) {
        printf("ERR: free unalloc/freed memory: %p\n", __ptr);
    } else {
        total_free += _trace_listGetByPos(store, pos)->size;
        _trace_listDeleteItem(store, pos);
    }
    free(__ptr);
}

void *_realloc(void *__ptr, size_t __size) {
    struct _trace_Data target = {__ptr, 0};
    int pos = _trace_listGetPosOrdered(store, &target);
    if (pos == -1) {
        printf("ERR: realloc unalloc/freed memory: %p\n", __ptr);
    } else {
        total_malloc += __size;
        total_free += _trace_listGetByPos(store, pos)->size;
        size_t current_memory = total_malloc - total_free;
        if (current_memory > max_memory) {
            max_memory = current_memory;
        }
        _trace_listDeleteItem(store, pos);
    }
    void *addr = realloc(__ptr, __size);
    struct _trace_Data newInfo = {addr, __size};
    _trace_listInsertItemOrdered(store, newInfo);
    return addr;
}

void traceSummarize() {
    printf("TRACE: total_alloc: %zu Bytes, total_free: %zu Bytes, max_memory: "
           "%zu Bytes\n",
           total_malloc, total_free, max_memory);
}

void _trace_destroyData(struct _trace_Data *data) { free(data); }

void _trace_printData(struct _trace_Data *data) {
    printf("addr = %p, size = %zu", data->addr, data->size);
}
int _trace_dataEquals(struct _trace_Data *a, struct _trace_Data *b) {
    if (a->addr == b->addr) {
        return 1;
    } else {
        return 0;
    }
}
int _trace_dataCmp(const void *a, const void *b) {
    struct _trace_Data *dA = *((struct _trace_Data **)a);
    struct _trace_Data *dB = *((struct _trace_Data **)b);
    if (dA->addr < dB->addr) {
        return -1;
    } else if (dA->addr > dB->addr) {
        return 1;
    } else {
        return 0;
    }
}