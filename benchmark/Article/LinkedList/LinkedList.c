#include "LinkedList.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

struct LinkedList *LinkedList_createList(struct LinkedList_Data *initData) {
    struct LinkedList *result =
        (struct LinkedList *)_malloc(sizeof(struct LinkedList));
    result->len = 1;

    struct LinkedList_Node *head =
        (struct LinkedList_Node *)_malloc(sizeof(struct LinkedList_Node));
    struct LinkedList_Data *_data =
        (struct LinkedList_Data *)_malloc(sizeof(struct LinkedList_Data));
    memcpy(_data, initData, sizeof(struct LinkedList_Data));
    head->next = NULL;

    result->head = head;
    head->d = _data;

    return result;
}

size_t LinkedList_getLength(struct LinkedList *lst) { return lst->len; }

void LinkedList_destroyList(struct LinkedList *lst) {
    struct LinkedList_Node *this = lst->head;
    while (this->next != NULL) {
        struct LinkedList_Node *next = this->next;
        LinkedList_destroyData(this->d);
        _free(this);
        this = next;
    }
    LinkedList_destroyData(this->d);
    _free(this);
    _free(lst);
}

void LinkedList_printLst(struct LinkedList *lst) {
    struct LinkedList_Node *this = lst->head;
    while (this->next != NULL) {
        LinkedList_printData(this->d);
        printf(", ");
        this = this->next;
    }
    LinkedList_printData(this->d);
    putchar('\n');
}

void LinkedList_insert(struct LinkedList *lst, struct LinkedList_Node *target,
                       struct LinkedList_Data *data) {
    struct LinkedList_Node *newNode =
        (struct LinkedList_Node *)_malloc(sizeof(struct LinkedList_Node));
    struct LinkedList_Data *newData =
        (struct LinkedList_Data *)_malloc(sizeof(struct LinkedList_Data));
    memcpy(newData, data, sizeof(struct LinkedList_Data));
    newNode->d = newData;
    newNode->next = target->next;
    target->next = newNode;
    lst->len++;
}

void LinkedList_insertFirst(struct LinkedList *lst,
                            struct LinkedList_Data *data) {
    struct LinkedList_Node *newHead =
        (struct LinkedList_Node *)_malloc(sizeof(struct LinkedList_Node));
    struct LinkedList_Data *newData =
        (struct LinkedList_Data *)_malloc(sizeof(struct LinkedList_Data));
    memcpy(newData, data, sizeof(struct LinkedList_Data));
    newHead->d = newData;
    newHead->next = lst->head;
    lst->head = newHead;
    lst->len++;
}

bool LinkedList_insertIndex(struct LinkedList *lst, size_t index,
                            struct LinkedList_Data *data) {
    if (index > lst->len) {
        return false;
    }

    if (index == 0) {
        LinkedList_insertFirst(lst, data);
    } else {
        struct LinkedList_Node *current = lst->head;
        for (size_t now = 0; now < index - 1; now++) {
            current = current->next;
        }
        LinkedList_insert(lst, current, data);
    }
    return true;
}

void LinkedList_insertOrdered(struct LinkedList *lst,
                              struct LinkedList_Data *data) {
    struct LinkedList_Node *current = lst->head;
    struct LinkedList_Node *new =
        (struct LinkedList_Node *)_malloc(sizeof(struct LinkedList_Node));
    struct LinkedList_Data *newData =
        (struct LinkedList_Data *)_malloc(sizeof(struct LinkedList_Data));
    memcpy(newData, data, sizeof(struct LinkedList_Data));
    new->d = newData;
    if (LinkedList_dataCmp(current->d, data) >= 0) {
        new->next = current;
        lst->head = new;
        lst->len++;
        return;
    }
    while (current->next != NULL) {
        if (LinkedList_dataCmp(current->next->d, data) >= 0) {
            new->next = current->next;
            current->next = new;
            lst->len++;
            return;
        }
        current = current->next;
    }
    new->next = NULL;
    current->next = new;
    lst->len++;
    return;
}

bool LinkedList_deleteIndex(struct LinkedList *lst, size_t index) {
    if (index >= lst->len) {
        return false;
    }

    struct LinkedList_Node *current = lst->head;
    for (size_t now = 0; now < index; now++) {
        current = current->next;
    }

    LinkedList_deleteNode(lst, current);
    return true;
}

struct LinkedList_Node *LinkedList_searchNode(struct LinkedList *lst,
                                              struct LinkedList_Data *data) {
    struct LinkedList_Node *this = lst->head;
    while (this->next != NULL) {
        if (LinkedList_dataEquals(this->d, data) == 1) {
            return this;
        }
        this = this->next;
    }
    if (LinkedList_dataEquals(this->d, data) == 1) {
        return this;
    } else {
        return NULL;
    }
}

struct LinkedList_Node *
LinkedList_searchNodeBeginAt(struct LinkedList_Node *begin,
                             struct LinkedList_Data *data) {
    struct LinkedList_Node *this = begin;
    while (this->next != NULL) {
        if (LinkedList_dataEquals(this->d, data) == 1) {
            return this;
        }
        this = this->next;
    }
    if (LinkedList_dataEquals(this->d, data) == 1) {
        return this;
    } else {
        return NULL;
    }
}

void LinkedList_deleteNode(struct LinkedList *lst,
                           struct LinkedList_Node *node) {
    if (node == lst->head) {
        lst->head = node->next;
        LinkedList_destroyData(node->d);
        _free(node);
        lst->len--;
    } else {
        struct LinkedList_Node *this = lst->head;
        while (this->next != NULL) {
            if (this->next == node) {
                this->next = node->next;
                LinkedList_destroyData(node->d);
                _free(node);
                lst->len--;
                return;
            } else {
                this = this->next;
            }
        }
    }
}

struct LinkedList_Node *LinkedList_getIndex(struct LinkedList *lst,
                                            size_t index) {
    if (index >= lst->len) {
        return NULL;
    }

    struct LinkedList_Node *current = lst->head;
    for (size_t now = 0; now < index; now++) {
        current = current->next;
    }

    return current;
}
