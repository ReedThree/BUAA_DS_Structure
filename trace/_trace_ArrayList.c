#include "_trace_ArrayList.h"
#include <stdlib.h>

int equalOrGreaterThan(struct _trace_Data **lst, int n,
                       struct _trace_Data *target);

struct _trace_ArrayList *_trace_createList(int capacity) {
    struct _trace_ArrayList *result =
        (struct _trace_ArrayList *)malloc(sizeof(struct _trace_ArrayList));
    result->lst = (struct _trace_Data **)malloc((unsigned)capacity *
                                                sizeof(struct _trace_Data *));
    result->capacity = capacity;
    result->len = 0;
    return result;
}

void _trace_destroyList(struct _trace_ArrayList *target) {
    for (int i = 0; i < target->len; i++) {
        _trace_destroyData(target->lst[i]);
    }
    free(target->lst);
    free(target);
}

void _trace_printList(struct _trace_ArrayList *target) {
    putchar('[');
    for (int i = 0; i < (target->len - 1); i++) {
        _trace_printData(target->lst[i]);
        printf(", ");
    }
    if (target->len > 0) {
        _trace_printData(target->lst[target->len - 1]);
    }

    printf("]\n");
}

struct _trace_Data *_trace_listGetByPos(struct _trace_ArrayList *lst, int pos) {
    if ((pos < 0) || (pos >= lst->len)) {
        return NULL;
    }
    return lst->lst[pos];
}

struct _trace_Data *_trace_listSearch(struct _trace_ArrayList *lst,
                                      struct _trace_Data data) {
    for (int i = 0; i < lst->len; i++) {
        if (_trace_dataEquals(lst->lst[i], &data)) {
            return lst->lst[i];
        }
    }
    return NULL;
}

struct _trace_Data *_trace_listSearchOrdered(struct _trace_ArrayList *lst,
                                             struct _trace_Data *data) {
    struct _trace_Data **r = (struct _trace_Data **)bsearch(
        &data, lst->lst, (unsigned)lst->len, sizeof(struct _trace_Data *),
        _trace_dataCmp);
    if (r == NULL) {
        return NULL;
    } else {
        return *r;
    }
}

int _trace_listGetPos(struct _trace_ArrayList *lst, struct _trace_Data *data) {
    for (int i = 0; i < lst->len; i++) {
        if (_trace_dataEquals(lst->lst[i], data)) {
            return i;
        }
    }
    return -1;
}

int _trace_listGetPosOrdered(struct _trace_ArrayList *lst,
                             struct _trace_Data *data) {
    struct _trace_Data **r = (struct _trace_Data **)bsearch(
        &data, lst->lst, (unsigned)lst->len, sizeof(struct _trace_Data *),
        _trace_dataCmp);
    if (r == NULL) {
        return -1;
    } else {
        return (int)(r - lst->lst);
    }
}

int _trace_listInsertItem(struct _trace_ArrayList *lst, int pos,
                          struct _trace_Data data) {
    if ((pos < 0) || (pos > lst->len)) {
        return 0;
    }

    struct _trace_Data *d =
        (struct _trace_Data *)malloc(sizeof(struct _trace_Data));
    *d = data;

    if (lst->len >= lst->capacity) {
        lst->capacity *= RESIZE_FACTOR;
        lst->lst = realloc(lst->lst, (unsigned)lst->capacity *
                                         sizeof(struct _trace_Data *));
    }

    for (int i = lst->len; i > pos; i--) {
        lst->lst[i] = lst->lst[i - 1];
    }
    lst->lst[pos] = d;
    lst->len++;

    return 1;
}

void _trace_listInsertItemOrdered(struct _trace_ArrayList *lst,
                                  struct _trace_Data data) {
    if (lst->len == 0) {
        _trace_listInsertItem(lst, 0, data);
    } else {
        int pos = equalOrGreaterThan(lst->lst, lst->len, &data);
        _trace_listInsertItem(lst, pos, data);
    }
}

int _trace_listDeleteItem(struct _trace_ArrayList *lst, int pos) {
    if ((pos < 0) || (pos >= lst->len)) {
        return 0;
    }

    _trace_destroyData(lst->lst[pos]);

    for (int i = pos; i < (lst->len - 1); i++) {
        lst->lst[i] = lst->lst[i + 1];
    }
    lst->len--;
    return 1;
}

void _trace_listSort(struct _trace_ArrayList *lst, __compar_fn_t compar) {
    qsort(lst->lst, (unsigned)lst->len, sizeof(struct _trace_Data *), compar);
}

int equalOrGreaterThan(struct _trace_Data **lst, int n,
                       struct _trace_Data *target) {
    int hi = n - 1;
    int lo = 0;
    int mid = (hi + lo) / 2;
    while (lo <= hi) {
        mid = (hi + lo) / 2;
        if (_trace_dataCmp(&lst[mid], &target) < 0) {
            lo = mid + 1;
        } else if (_trace_dataCmp(&lst[mid], &target) > 0) {
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
