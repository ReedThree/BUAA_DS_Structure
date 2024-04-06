#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdbool.h>
#include <stddef.h>

// Impl by user
struct LinkedList_Data {
    int c;
    int p;
};
void LinkedList_destroyData(struct LinkedList_Data *target);
void LinkedList_printData(struct LinkedList_Data *data);
int LinkedList_dataEquals(struct LinkedList_Data *a, struct LinkedList_Data *b);
int LinkedList_dataCmp(struct LinkedList_Data *a, struct LinkedList_Data *b);
// --------------

struct LinkedList_Node {
    struct LinkedList_Data *d;
    struct LinkedList_Node *next;
};

struct LinkedList {
    struct LinkedList_Node *head;
    size_t len;
};

struct LinkedList *LinkedList_createList(struct LinkedList_Data *initData);
size_t LinkedList_getLength(struct LinkedList *lst);
void LinkedList_destroyList(struct LinkedList *lst);
void LinkedList_printLst(struct LinkedList *lst);
void LinkedList_insert(struct LinkedList *lst, struct LinkedList_Node *target,
                       struct LinkedList_Data *data);
void LinkedList_insertFirst(struct LinkedList *lst,
                            struct LinkedList_Data *data);
void LinkedList_insertOrdered(struct LinkedList *lst,
                              struct LinkedList_Data *data);
bool LinkedList_insertIndex(struct LinkedList *lst, size_t index,
                            struct LinkedList_Data *data);
struct LinkedList_Node *LinkedList_searchNode(struct LinkedList *lst,
                                              struct LinkedList_Data *data);
struct LinkedList_Node *
LinkedList_searchNodeBeginAt(struct LinkedList_Node *begin,
                             struct LinkedList_Data *data);
void LinkedList_deleteNode(struct LinkedList *lst,
                           struct LinkedList_Node *node);
bool LinkedList_deleteIndex(struct LinkedList *lst, size_t index);
struct LinkedList_Node *LinkedList_getIndex(struct LinkedList *lst,
                                            size_t index);
#endif
