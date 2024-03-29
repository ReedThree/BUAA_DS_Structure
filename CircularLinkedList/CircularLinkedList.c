#include "CircularLinkedList.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

struct CircularLinkedList *
CircularLinkedList_createList(struct CircularLinkedList_Data *initData) {
    struct CircularLinkedList *result =
        (struct CircularLinkedList *)_malloc(sizeof(struct CircularLinkedList));
    result->len = 1;

    struct CircularLinkedList_Node *head =
        (struct CircularLinkedList_Node *)_malloc(
            sizeof(struct CircularLinkedList_Node));
    struct CircularLinkedList_Data *_data =
        (struct CircularLinkedList_Data *)_malloc(
            sizeof(struct CircularLinkedList_Data));
    memcpy(_data, initData, sizeof(struct CircularLinkedList_Data));
    head->next = head;
    head->d = _data;

    result->head = head;

    return result;
}

int CircularLinkedList_getLength(struct CircularLinkedList *lst) {
    return lst->len;
}

void CircularLinkedList_destroyList(struct CircularLinkedList *lst) {
    struct CircularLinkedList_Node *this = lst->head;
    for (int i = 0; i < lst->len; i++) {
        struct CircularLinkedList_Node *temp = this->next;
        CircularLinkedList_destroyData(this->d);
        _free(this);
        this = temp;
    }
    _free(lst);
}

void CircularLinkedList_printLst(struct CircularLinkedList *lst) {
    struct CircularLinkedList_Node *this = lst->head;
    if (lst->len == 0) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; i < (lst->len - 1); i++) {
        CircularLinkedList_printData(this->d);
        printf(", ");
        this = this->next;
    }
    CircularLinkedList_printData(this->d);
    putchar('\n');
}

void CircularLinkedList_printLstWithNum(struct CircularLinkedList *lst,
                                        int num) {
    struct CircularLinkedList_Node *this = lst->head;
    if (lst->len == 0) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; i < (num - 1); i++) {
        CircularLinkedList_printData(this->d);
        printf(", ");
        this = this->next;
    }
    CircularLinkedList_printData(this->d);
    putchar('\n');
}

void CircularLinkedList_insert(struct CircularLinkedList *lst,
                               struct CircularLinkedList_Node *target,
                               struct CircularLinkedList_Data *data) {
    struct CircularLinkedList_Node *newNode =
        (struct CircularLinkedList_Node *)_malloc(
            sizeof(struct CircularLinkedList_Node));
    struct CircularLinkedList_Data *newData =
        (struct CircularLinkedList_Data *)_malloc(
            sizeof(struct CircularLinkedList_Data));
    memcpy(newData, data, sizeof(struct CircularLinkedList_Data));
    newNode->d = newData;
    newNode->next = target->next;
    target->next = newNode;
    lst->len++;
}

void CircularLinkedList_insertFirst(struct CircularLinkedList *lst,
                                    struct CircularLinkedList_Data *data) {
    struct CircularLinkedList_Node *newHead =
        (struct CircularLinkedList_Node *)_malloc(
            sizeof(struct CircularLinkedList_Node));
    struct CircularLinkedList_Data *newData =
        (struct CircularLinkedList_Data *)_malloc(
            sizeof(struct CircularLinkedList_Data));
    memcpy(newData, data, sizeof(struct CircularLinkedList_Data));
    struct CircularLinkedList_Node *head = lst->head;
    struct CircularLinkedList_Node *current = head;
    while (current->next != head) {
        current = current->next;
    }

    current->next = newHead;

    newHead->d = newData;
    newHead->next = lst->head;
    lst->head = newHead;
    lst->len++;
}

int CircularLinkedList_insertIndex(struct CircularLinkedList *lst, int index,
                                   struct CircularLinkedList_Data *data) {
    if (index < 0) {
        return -1;
    }

    if (index == 0) {
        CircularLinkedList_insertFirst(lst, data);
    } else {
        struct CircularLinkedList_Node *current = lst->head;
        for (int now = 0; now < index - 1; now++) {
            current = current->next;
        }
        CircularLinkedList_insert(lst, current, data);
    }
    return 0;
}

int CircularLinkedList_deleteIndex(struct CircularLinkedList *lst, int index) {
    if (index < 0) {
        return -1;
    }

    struct CircularLinkedList_Node *current = lst->head;
    for (int now = 0; now < index; now++) {
        current = current->next;
    }

    CircularLinkedList_deleteNode(lst, current);
    return 0;
}

struct CircularLinkedList_Node *
CircularLinkedList_searchNode(struct CircularLinkedList *lst,
                              struct CircularLinkedList_Data *data) {
    struct CircularLinkedList_Node *this = lst->head;
    for (int i = 0; i < lst->len; i++) {
        if (CircularLinkedList_dataEquals(this->d, data) == 1) {
            return this;
        }
        this = this->next;
    }
    return NULL;
}

struct CircularLinkedList_Node *
CircularLinkedList_searchNodeBeginAt(struct CircularLinkedList *lst,
                                     struct CircularLinkedList_Node *begin,
                                     struct CircularLinkedList_Data *data) {
    struct CircularLinkedList_Node *this = begin;
    for (int i = 0; i < lst->len; i++) {
        if (CircularLinkedList_dataEquals(this->d, data) == 1) {
            return this;
        }
        this = this->next;
    }
    return NULL;
}

void CircularLinkedList_deleteNode(struct CircularLinkedList *lst,
                                   struct CircularLinkedList_Node *node) {
    if (node == lst->head) {
        lst->head = node->next;
        struct CircularLinkedList_Node *this = node;
        while (this->next != NULL) {
            if (this->next == node) {
                this->next = node->next;
                CircularLinkedList_destroyData(node->d);
                _free(node);
                lst->len--;
                return;
            } else {
                this = this->next;
            }
        }
    } else {
        struct CircularLinkedList_Node *this = lst->head;
        while (this->next != NULL) {
            if (this->next == node) {
                this->next = node->next;
                _free(node);
                lst->len--;
                return;
            } else {
                this = this->next;
            }
        }
    }
}

struct CircularLinkedList_Node *
CircularLinkedList_getIndex(struct CircularLinkedList *lst, int index) {
    if (index < 0) {
        return NULL;
    }

    struct CircularLinkedList_Node *current = lst->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}

struct CircularLinkedList_Node *
CircularLinkedList_seekNode(struct CircularLinkedList_Node *source, int step) {
    struct CircularLinkedList_Node *result = source;
    for (int i = 0; i < step; i++) {
        result = result->next;
    }
    return result;
}
