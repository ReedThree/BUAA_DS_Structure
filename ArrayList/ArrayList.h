#ifndef __ARRAY_LIST_H
#define __ARRAY_LIST_H

#include <stdbool.h>
#include <stdlib.h>

#define RESIZE_FACTOR 2

// imply by user
struct ArrayList_Data {
    const char *word;
    int count;
};
void ArrayList_destroyData(struct ArrayList_Data *target);
void ArrayList_printData(struct ArrayList_Data *target);
int ArrayList_dataEquals(struct ArrayList_Data *a, struct ArrayList_Data *b);
int ArrayList_dataCmp(const void *a, const void *b);
// ----
struct ArrayList {
    struct ArrayList_Data **lst;
    size_t capacity;
    size_t len;
};

struct ArrayList *ArrayList_createList(size_t capacity);
void ArrayList_destroyList(struct ArrayList *target);
size_t ArrayList_getLength(struct ArrayList *lst);
void ArrayList_printList(struct ArrayList *target);
struct ArrayList_Data *ArrayList_getByPos(struct ArrayList *lst, size_t pos);
struct ArrayList_Data *ArrayList_search(struct ArrayList *lst,
                                        struct ArrayList_Data *data);
struct ArrayList_Data *ArrayList_searchOrdered(struct ArrayList *lst,
                                               struct ArrayList_Data *data);
long long ArrayList_getPos(struct ArrayList *lst, struct ArrayList_Data *data);
long long ArrayList_getPosOrdered(struct ArrayList *lst,
                                  struct ArrayList_Data *data);
bool ArrayList_insertItem(struct ArrayList *lst, size_t pos,
                          struct ArrayList_Data *data);
void ArrayList_insertItemOrdered(struct ArrayList *lst,
                                 struct ArrayList_Data *data);
bool ArrayList_deleteItem(struct ArrayList *lst, size_t pos);
void ArrayList_sort(struct ArrayList *lst, __compar_fn_t compar);

#endif
