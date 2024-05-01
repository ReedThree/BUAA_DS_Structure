#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdbool.h>
#include <stddef.h>

struct LinkedList_Node {
    char *word;
    int count;
    struct LinkedList_Node *next;
};

struct LinkedList {
    struct LinkedList_Node *head;
    size_t len;
};

struct LinkedList *LinkedList_createList(void);
void LinkedList_insertFirst(struct LinkedList *lst, char *data);
struct LinkedList_Node *LinkedList_searchNode(struct LinkedList *lst,
                                              char *data);
void LinkedList_destroyList(struct LinkedList *lst);
#endif
