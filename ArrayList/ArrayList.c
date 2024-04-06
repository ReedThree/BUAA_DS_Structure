#include "ArrayList.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

long long ArrayList_equalOrGreaterThan(struct ArrayList_Data **lst, long long n,
                                       struct ArrayList_Data *target);

struct ArrayList *ArrayList_createList(size_t capacity) {
    struct ArrayList *result =
        (struct ArrayList *)_malloc(sizeof(struct ArrayList));
    result->lst = (struct ArrayList_Data **)_malloc(
        capacity * sizeof(struct ArrayList_Data *));
    result->capacity = capacity;
    result->len = 0;
    return result;
}

void ArrayList_destroyList(struct ArrayList *target) {
    for (size_t i = 0; i < target->len; i++) {
        ArrayList_destroyData(target->lst[i]);
    }
    _free(target->lst);
    _free(target);
}

size_t ArrayList_getLength(struct ArrayList *lst) { return lst->len; }

void ArrayList_printList(struct ArrayList *target) {
    putchar('[');
    if (target->len > 0) {
        for (size_t i = 0; i < (target->len - 1); i++) {
            ArrayList_printData(target->lst[i]);
            printf(", ");
        }
        ArrayList_printData(target->lst[target->len - 1]);
    }

    printf("]\n");
}

struct ArrayList_Data *ArrayList_getByPos(struct ArrayList *lst, size_t pos) {
    if (pos >= lst->len) {
        return NULL;
    }
    return lst->lst[pos];
}

struct ArrayList_Data *ArrayList_search(struct ArrayList *lst,
                                        struct ArrayList_Data *data) {
    for (size_t i = 0; i < lst->len; i++) {
        if (ArrayList_dataEquals(lst->lst[i], data)) {
            return lst->lst[i];
        }
    }
    return NULL;
}

struct ArrayList_Data *ArrayList_searchOrdered(struct ArrayList *lst,
                                               struct ArrayList_Data *data) {
    struct ArrayList_Data **r = (struct ArrayList_Data **)bsearch(
        &data, lst->lst, lst->len, sizeof(struct ArrayList_Data *),
        ArrayList_dataCmp);
    if (r == NULL) {
        return NULL;
    } else {
        return *r;
    }
}

long long ArrayList_getPos(struct ArrayList *lst, struct ArrayList_Data *data) {
    for (size_t i = 0; i < lst->len; i++) {
        if (ArrayList_dataEquals(lst->lst[i], data)) {
            return (long long)i;
        }
    }
    return -1;
}

long long ArrayList_getPosOrdered(struct ArrayList *lst,
                                  struct ArrayList_Data *data) {
    struct ArrayList_Data **r = (struct ArrayList_Data **)bsearch(
        &data, lst->lst, lst->len, sizeof(struct ArrayList_Data *),
        ArrayList_dataCmp);
    if (r == NULL) {
        return -1;
    } else {
        return (int)(r - lst->lst);
    }
}

bool ArrayList_insertItem(struct ArrayList *lst, size_t pos,
                          struct ArrayList_Data *data) {
    if (pos > lst->len) {
        return 0;
    }

    struct ArrayList_Data *d =
        (struct ArrayList_Data *)_malloc(sizeof(struct ArrayList_Data));
    memcpy(d, data, sizeof(struct ArrayList_Data));

    if (lst->len >= lst->capacity) {
        lst->capacity *= RESIZE_FACTOR;
        lst->lst =
            _realloc(lst->lst, lst->capacity * sizeof(struct ArrayList_Data *));
    }

    for (size_t i = lst->len; i > pos; i--) {
        lst->lst[i] = lst->lst[i - 1];
    }
    lst->lst[pos] = d;
    lst->len++;

    return 1;
}

void ArrayList_insertItemOrdered(struct ArrayList *lst,
                                 struct ArrayList_Data *data) {
    if (lst->len == 0) {
        ArrayList_insertItem(lst, 0, data);
    } else {
        size_t pos = (size_t)ArrayList_equalOrGreaterThan(
            lst->lst, (long long)lst->len, data);
        ArrayList_insertItem(lst, pos, data);
    }
}

bool ArrayList_deleteItem(struct ArrayList *lst, size_t pos) {
    if (pos >= lst->len) {
        return 0;
    }

    ArrayList_destroyData(lst->lst[pos]);

    for (size_t i = pos; i < (lst->len - 1); i++) {
        lst->lst[i] = lst->lst[i + 1];
    }
    lst->len--;
    return 1;
}

void ArrayList_sort(struct ArrayList *lst, __compar_fn_t compar) {
    qsort(lst->lst, (unsigned)lst->len, sizeof(struct ArrayList_Data *),
          compar);
}

long long ArrayList_equalOrGreaterThan(struct ArrayList_Data **lst, long long n,
                                       struct ArrayList_Data *target) {
    long long hi = n - 1;
    long long lo = 0;
    long long mid = (hi + lo) / 2;
    while (lo <= hi) {
        mid = (hi + lo) / 2;
        if (ArrayList_dataCmp(&lst[mid], &target) < 0) {
            lo = mid + 1;
        } else if (ArrayList_dataCmp(&lst[mid], &target) > 0) {
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
