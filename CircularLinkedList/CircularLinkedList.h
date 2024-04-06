#ifndef __CIRCULARLINKEDLIST_H__
#define __CIRCULARLINKEDLIST_H__

#include <stddef.h>

// Impl by user
struct CircularLinkedList_Data {
    int c;
    int p;
};
void CircularLinkedList_destroyData(struct CircularLinkedList_Data *target);
void CircularLinkedList_printData(struct CircularLinkedList_Data *data);
int CircularLinkedList_dataEquals(struct CircularLinkedList_Data *a,
                                  struct CircularLinkedList_Data *b);
int CircularLinkedList_dataCmp(struct CircularLinkedList_Data *a,
                               struct CircularLinkedList_Data *b);
// --------------

struct CircularLinkedList_Node {
    struct CircularLinkedList_Data *d;
    struct CircularLinkedList_Node *next;
};

struct CircularLinkedList {
    struct CircularLinkedList_Node *head;
    size_t len;
};

// index 可大于链表长度，将循环

struct CircularLinkedList *
CircularLinkedList_createList(struct CircularLinkedList_Data *initData);
size_t CircularLinkedList_getLength(struct CircularLinkedList *lst);
void CircularLinkedList_destroyList(struct CircularLinkedList *lst);
void CircularLinkedList_printLst(struct CircularLinkedList *lst);
void CircularLinkedList_printLstWithNum(struct CircularLinkedList *lst,
                                        size_t num);
void CircularLinkedList_insert(struct CircularLinkedList *lst,
                               struct CircularLinkedList_Node *target,
                               struct CircularLinkedList_Data *data);
void CircularLinkedList_insertFirst(struct CircularLinkedList *lst,
                                    struct CircularLinkedList_Data *data);
void CircularLinkedList_insertIndex(struct CircularLinkedList *lst,
                                    size_t index,
                                    struct CircularLinkedList_Data *data);
struct CircularLinkedList_Node *
CircularLinkedList_searchNode(struct CircularLinkedList *lst,
                              struct CircularLinkedList_Data *data);
struct CircularLinkedList_Node *
CircularLinkedList_searchNodeBeginAt(struct CircularLinkedList *lst,
                                     struct CircularLinkedList_Node *begin,
                                     struct CircularLinkedList_Data *data);
void CircularLinkedList_deleteNode(struct CircularLinkedList *lst,
                                   struct CircularLinkedList_Node *node);
void CircularLinkedList_deleteIndex(struct CircularLinkedList *lst,
                                    size_t index);
struct CircularLinkedList_Node *
CircularLinkedList_getIndex(struct CircularLinkedList *lst, size_t index);
struct CircularLinkedList_Node *
CircularLinkedList_seekNode(struct CircularLinkedList_Node *source,
                            size_t step);
#endif
