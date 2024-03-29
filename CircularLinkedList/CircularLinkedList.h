#ifndef __CIRCULARLINKEDLIST_H__
#define __CIRCULARLINKEDLIST_H__

// Impl by user
struct CircularLinkedList_Data {
    int c;
    int p;
};
void CircularLinkedList_destroyData(struct CircularLinkedList_Data *target);
void CircularLinkedList_printData(struct CircularLinkedList_Data *data);
int CircularLinkedList_dataEquals(struct CircularLinkedList_Data *a, struct CircularLinkedList_Data *b);
int CircularLinkedList_dataCmp(struct CircularLinkedList_Data *a, struct CircularLinkedList_Data *b);
// --------------

struct CircularLinkedList_Node {
    struct CircularLinkedList_Data *d;
    struct CircularLinkedList_Node *next;
};

struct CircularLinkedList {
    struct CircularLinkedList_Node *head;
    int len;
};

// index 可大于链表长度，将循环

struct CircularLinkedList *CircularLinkedList_createList(struct CircularLinkedList_Data *initData);
int CircularLinkedList_getLength(struct CircularLinkedList *lst);
void CircularLinkedList_destroyList(struct CircularLinkedList *lst);
void CircularLinkedList_printLst(struct CircularLinkedList *lst);
void CircularLinkedList_printLstWithNum(struct CircularLinkedList *lst, int num);
void CircularLinkedList_insert(struct CircularLinkedList *lst, struct CircularLinkedList_Node *target, struct CircularLinkedList_Data *data);
void CircularLinkedList_insertFirst(struct CircularLinkedList *lst, struct CircularLinkedList_Data *data);
int CircularLinkedList_insertIndex(struct CircularLinkedList *lst, int index, struct CircularLinkedList_Data *data);
struct CircularLinkedList_Node *CircularLinkedList_searchNode(struct CircularLinkedList *lst, struct CircularLinkedList_Data *data);
struct CircularLinkedList_Node *CircularLinkedList_searchNodeBeginAt(struct CircularLinkedList *lst,
                               struct CircularLinkedList_Node *begin, struct CircularLinkedList_Data *data);
void CircularLinkedList_deleteNode(struct CircularLinkedList *lst, struct CircularLinkedList_Node *node);
int CircularLinkedList_deleteIndex(struct CircularLinkedList *lst, int index);
struct CircularLinkedList_Node *CircularLinkedList_getIndex(struct CircularLinkedList *lst, int index);
struct CircularLinkedList_Node *CircularLinkedList_seekNode(struct CircularLinkedList_Node *source, int step);
#endif
