#ifndef __DOUBLELINKEDLIST_H__
#define __DOUBLELINKEDLIST_H__

#include <stdbool.h>
#include <stddef.h>

// Impl by user
struct DoubleLinkedList_Data {
    int c;
    int p;
};
void DoubleLinkedList_destroyData(struct DoubleLinkedList_Data *target);
void DoubleLinkedList_printData(struct DoubleLinkedList_Data *data);
int DoubleLinkedList_dataEquals(struct DoubleLinkedList_Data *a,
                                struct DoubleLinkedList_Data *b);
int DoubleLinkedList_dataCmp(struct DoubleLinkedList_Data *a,
                             struct DoubleLinkedList_Data *b);
// --------------

struct DoubleLinkedList_Node {
    struct DoubleLinkedList_Data *d;
    struct DoubleLinkedList_Node *prev;
    struct DoubleLinkedList_Node *next;
};

struct DoubleLinkedList {
    struct DoubleLinkedList_Node *head;
    struct DoubleLinkedList_Node *tail;
    size_t len;
};

struct DoubleLinkedList *
DoubleLinkedList_createList(struct DoubleLinkedList_Data *initData);
size_t DoubleLinkedList_getLength(struct DoubleLinkedList *lst);
void DoubleLinkedList_printLst(struct DoubleLinkedList *lst);
void DoubleLinkedList_printLstReversed(struct DoubleLinkedList *lst);
void DoubleLinkedList_destroyList(struct DoubleLinkedList *lst);
void DoubleLinkedList_insertAfter(struct DoubleLinkedList *lst,
                                  struct DoubleLinkedList_Node *target,
                                  struct DoubleLinkedList_Data *data);
void DoubleLinkedList_insertBefore(struct DoubleLinkedList *lst,
                                   struct DoubleLinkedList_Node *target,
                                   struct DoubleLinkedList_Data *data);
void DoubleLinkedList_insertOrdered(struct DoubleLinkedList *lst,
                                    struct DoubleLinkedList_Data *data);
bool DoubleLinkedList_insertIndex(struct DoubleLinkedList *lst, size_t index,
                                  struct DoubleLinkedList_Data *data);
bool DoubleLinkedList_insertIndexReversed(struct DoubleLinkedList *lst,
                                          size_t index,
                                          struct DoubleLinkedList_Data *data);
void DoubleLinkedList_forEach(struct DoubleLinkedList *lst,
                              void (*op)(struct DoubleLinkedList_Node *));
void DoubleLinkedList_forEachReversed(
    struct DoubleLinkedList *lst, void (*op)(struct DoubleLinkedList_Node *));
struct DoubleLinkedList_Node *
DoubleLinkedList_searchNode(struct DoubleLinkedList *lst,
                            struct DoubleLinkedList_Data *data);
struct DoubleLinkedList_Node *
DoubleLinkedList_searchNodeBeginAt(struct DoubleLinkedList_Node *begin,
                                   struct DoubleLinkedList_Data *data);
void DoubleLinkedList_deleteNode(struct DoubleLinkedList *lst,
                                 struct DoubleLinkedList_Node *node);
bool DoubleLinkedList_deleteIndex(struct DoubleLinkedList *lst, size_t index);
bool DoubleLinkedList_deleteIndexReversed(struct DoubleLinkedList *lst,
                                          size_t index);
size_t DoubleLinkedList_getNodeIndex(struct DoubleLinkedList *lst,
                                     struct DoubleLinkedList_Node *target);
struct DoubleLinkedList_Node *
DoubleLinkedList_getByIndex(struct DoubleLinkedList *lst, size_t index);
void DoubleLinkedList_push(struct DoubleLinkedList *lst,
                           struct DoubleLinkedList_Data *data);
struct DoubleLinkedList_Data *
DoubleLinkedList_pop(struct DoubleLinkedList *lst);

#endif
