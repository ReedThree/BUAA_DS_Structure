#include "ArrayList.h"
#include <stdlib.h>

int equalOrGreaterThan(struct Data **lst, int n, struct Data *target);

struct ArrayList *createList(int capacity) {
    struct ArrayList *result =
        (struct ArrayList *)_malloc(sizeof(struct ArrayList));
    result->lst =
        (struct Data **)_malloc((unsigned)capacity * sizeof(struct Data *));
    result->capacity = capacity;
    result->len = 0;
    return result;
}

void destroyList(struct ArrayList *target) {
    for (int i = 0; i < target->len; i++) {
        destroyData(target->lst[i]);
    }
    _free(target->lst);
    _free(target);
}

void printList(struct ArrayList *target) {
    putchar('[');
    for (int i = 0; i < (target->len - 1); i++) {
        printData(target->lst[i]);
        printf(", ");
    }
    if (target->len > 0) {
        printData(target->lst[target->len - 1]);
    }

    printf("]\n");
}

struct Data *listGetByPos(struct ArrayList *lst, int pos) {
    if ((pos < 0) || (pos >= lst->len)) {
        return NULL;
    }
    return lst->lst[pos];
}

struct Data *listSearch(struct ArrayList *lst, struct Data data) {
    for (int i = 0; i < lst->len; i++) {
        if (dataEquals(lst->lst[i], &data)) {
            return lst->lst[i];
        }
    }
    return NULL;
}

struct Data *listSearchOrdered(struct ArrayList *lst, struct Data *data) {
    struct Data **r = (struct Data **)bsearch(
        &data, lst->lst, (unsigned)lst->len, sizeof(struct Data *), dataCmp);
    if (r == NULL) {
        return NULL;
    } else {
        return *r;
    }
}

int listInsertItem(struct ArrayList *lst, int pos, struct Data data) {
    if ((pos < 0) || (pos > lst->len)) {
        return 0;
    }

    struct Data *d = (struct Data *)_malloc(sizeof(struct Data));
    *d = data;

    if (lst->len >= lst->capacity) {
        lst->capacity *= RESIZE_FACTOR;
        lst->lst =
            _realloc(lst->lst, (unsigned)lst->capacity * sizeof(struct Data *));
    }

    for (int i = lst->len; i > pos; i--) {
        lst->lst[i] = lst->lst[i - 1];
    }
    lst->lst[pos] = d;
    lst->len++;

    return 1;
}

void listInsertItemOrdered(struct ArrayList *lst, struct Data data) {
    if (lst->len == 0) {
        listInsertItem(lst, 0, data);
    } else {
        int pos = equalOrGreaterThan(lst->lst, lst->len, &data);
        listInsertItem(lst, pos, data);
    }
}

int listDeleteItem(struct ArrayList *lst, int pos) {
    if ((pos < 0) || (pos >= lst->len)) {
        return 0;
    }

    destroyData(lst->lst[pos]);

    for (int i = pos; i < (lst->len - 1); i++) {
        lst->lst[i] = lst->lst[i + 1];
    }
    lst->len--;
    return 1;
}

void listSort(struct ArrayList *lst, __compar_fn_t compar) {
    qsort(lst->lst, (unsigned)lst->len, sizeof(struct Data *), compar);
}

int equalOrGreaterThan(struct Data **lst, int n, struct Data *target) {
    int hi = n - 1;
    int lo = 0;
    int mid = (hi + lo) / 2;
    while (lo <= hi) {
        mid = (hi + lo) / 2;
        if (dataCmp(&lst[mid], &target) < 0) {
            lo = mid + 1;
        } else if (dataCmp(&lst[mid], &target) > 0) {
            hi = mid - 1;
        } else {
            hi = mid - 1;
        }
    }
    if (lo < 0) {
        return 0;
    }
    return lo;
}

void *_malloc(size_t __size) { return malloc(__size); }
void _free(void *__ptr) { free(__ptr); }
void *_realloc(void *__ptr, size_t __size) { return realloc(__ptr, __size); }