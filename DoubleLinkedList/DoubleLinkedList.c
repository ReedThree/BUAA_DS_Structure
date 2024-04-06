#include "DoubleLinkedList.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

struct DoubleLinkedList *
DoubleLinkedList_createList(struct DoubleLinkedList_Data *initData) {
    struct DoubleLinkedList *result =
        (struct DoubleLinkedList *)_malloc(sizeof(struct DoubleLinkedList));

    struct DoubleLinkedList_Node *initNode =
        (struct DoubleLinkedList_Node *)_malloc(
            sizeof(struct DoubleLinkedList_Node));
    initNode->next = NULL;
    initNode->prev = NULL;

    struct DoubleLinkedList_Data *_initData =
        (struct DoubleLinkedList_Data *)_malloc(
            sizeof(struct DoubleLinkedList_Data));
    memcpy(_initData, initData, sizeof(struct DoubleLinkedList_Data));
    initNode->d = _initData;

    result->head = initNode;
    result->tail = initNode;
    result->len = 1;
    return result;
}

size_t DoubleLinkedList_getLength(struct DoubleLinkedList *lst) {
    return lst->len;
}

void DoubleLinkedList_destroyList(struct DoubleLinkedList *lst) {
    struct DoubleLinkedList_Node *current = lst->head;
    for (size_t i = 0; i < lst->len; i++) {
        struct DoubleLinkedList_Node *temp = current->next;
        DoubleLinkedList_destroyData(current->d);
        _free(current);
        current = temp;
    }
    _free(lst);
}

void DoubleLinkedList_printLst(struct DoubleLinkedList *lst) {
    struct DoubleLinkedList_Node *this = lst->head;
    if (lst->len == 0) {
        printf("NULL\n");
        return;
    }
    for (size_t i = 0; i < (lst->len - 1); i++) {
        DoubleLinkedList_printData(this->d);
        printf(", ");
        this = this->next;
    }
    DoubleLinkedList_printData(this->d);
    putchar('\n');
}

void DoubleLinkedList_printLstReversed(struct DoubleLinkedList *lst) {
    struct DoubleLinkedList_Node *this = lst->tail;
    if (lst->len == 0) {
        printf("NULL\n");
        return;
    }
    for (size_t i = 0; i < (lst->len - 1); i++) {
        DoubleLinkedList_printData(this->d);
        printf(", ");
        this = this->prev;
    }
    DoubleLinkedList_printData(this->d);
    putchar('\n');
}

void DoubleLinkedList_insertAfter(struct DoubleLinkedList *lst,
                                  struct DoubleLinkedList_Node *target,
                                  struct DoubleLinkedList_Data *data) {
    struct DoubleLinkedList_Node *newNode =
        (struct DoubleLinkedList_Node *)_malloc(
            sizeof(struct DoubleLinkedList_Node));
    struct DoubleLinkedList_Data *newData =
        (struct DoubleLinkedList_Data *)_malloc(
            sizeof(struct DoubleLinkedList_Data));
    memcpy(newData, data, sizeof(struct DoubleLinkedList_Data));
    newNode->d = newData;
    newNode->next = target->next;
    newNode->prev = target;

    if (target->next != NULL) {
        target->next->prev = newNode;
    } else {
        lst->tail = newNode;
    }

    target->next = newNode;
    lst->len++;
}

void DoubleLinkedList_insertBefore(struct DoubleLinkedList *lst,
                                   struct DoubleLinkedList_Node *target,
                                   struct DoubleLinkedList_Data *data) {
    struct DoubleLinkedList_Node *newNode =
        (struct DoubleLinkedList_Node *)_malloc(
            sizeof(struct DoubleLinkedList_Node));
    struct DoubleLinkedList_Data *newData =
        (struct DoubleLinkedList_Data *)_malloc(
            sizeof(struct DoubleLinkedList_Data));
    memcpy(newData, data, sizeof(struct DoubleLinkedList_Data));
    newNode->d = newData;
    newNode->next = target;
    newNode->prev = target->prev;

    if (target->prev != NULL) {
        target->prev->next = newNode;
    } else {
        lst->head = newNode;
    }

    target->prev = newNode;
    lst->len++;
}

void DoubleLinkedList_insertOrdered(struct DoubleLinkedList *lst,
                                    struct DoubleLinkedList_Data *data) {
    struct DoubleLinkedList_Node *current = lst->head;
    while ((DoubleLinkedList_dataCmp(current->d, data) < 0) &&
           (current->next != NULL)) {
        current = current->next;
    }

    if (current->next != NULL) {
        DoubleLinkedList_insertBefore(lst, current, data);
    } else {
        if (DoubleLinkedList_dataCmp(current->d, data) > 0) {
            DoubleLinkedList_insertBefore(lst, current, data);
        } else {
            DoubleLinkedList_insertAfter(lst, current, data);
        }
    }
}

bool DoubleLinkedList_insertIndex(struct DoubleLinkedList *lst, size_t index,
                                  struct DoubleLinkedList_Data *data) {
    if (index > lst->len) {
        return false;
    }

    if (index != lst->len) {
        struct DoubleLinkedList_Node *current = lst->head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        DoubleLinkedList_insertBefore(lst, current, data);
    } else {
        DoubleLinkedList_insertAfter(lst, lst->tail, data);
    }
    return true;
}

bool DoubleLinkedList_insertIndexReversed(struct DoubleLinkedList *lst,
                                          size_t index,
                                          struct DoubleLinkedList_Data *data) {
    if (index >= lst->len) {
        return false;
    }

    struct DoubleLinkedList_Node *current = lst->tail;
    for (size_t i = 0; i < index; i++) {
        current = current->prev;
    }
    DoubleLinkedList_insertAfter(lst, current, data);

    return true;
}

void DoubleLinkedList_forEach(struct DoubleLinkedList *lst,
                              void (*op)(struct DoubleLinkedList_Node *)) {
    struct DoubleLinkedList_Node *current = lst->head;
    for (size_t i = 0; i < lst->len; i++) {
        op(current);
        current = current->next;
    }
}

void DoubleLinkedList_forEachReversed(
    struct DoubleLinkedList *lst, void (*op)(struct DoubleLinkedList_Node *)) {
    struct DoubleLinkedList_Node *current = lst->tail;
    for (size_t i = 0; i < lst->len; i++) {
        op(current);
        current = current->prev;
    }
}

struct DoubleLinkedList_Node *
DoubleLinkedList_searchNode(struct DoubleLinkedList *lst,
                            struct DoubleLinkedList_Data *data) {
    struct DoubleLinkedList_Node *this = lst->head;
    while (this->next != NULL) {
        if (DoubleLinkedList_dataEquals(this->d, data) == 1) {
            return this;
        }
        this = this->next;
    }
    if (DoubleLinkedList_dataEquals(this->d, data) == 1) {
        return this;
    } else {
        return NULL;
    }
}

struct DoubleLinkedList_Node *
DoubleLinkedList_searchNodeBeginAt(struct DoubleLinkedList_Node *begin,
                                   struct DoubleLinkedList_Data *data) {
    struct DoubleLinkedList_Node *this = begin;
    while (this->next != NULL) {
        if (DoubleLinkedList_dataEquals(this->d, data) == 1) {
            return this;
        }
        this = this->next;
    }
    if (DoubleLinkedList_dataEquals(this->d, data) == 1) {
        return this;
    } else {
        return NULL;
    }
}

void DoubleLinkedList_deleteNode(struct DoubleLinkedList *lst,
                                 struct DoubleLinkedList_Node *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        lst->head = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        lst->tail = node->prev;
    }
    DoubleLinkedList_destroyData(node->d);
    _free(node);
    lst->len--;
}
bool DoubleLinkedList_deleteIndex(struct DoubleLinkedList *lst, size_t index) {
    if (index >= lst->len) {
        return false;
    }
    struct DoubleLinkedList_Node *current = lst->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    DoubleLinkedList_deleteNode(lst, current);
    return true;
}

bool DoubleLinkedList_deleteIndexReversed(struct DoubleLinkedList *lst,
                                          size_t index) {
    if (index >= lst->len) {
        return false;
    }
    struct DoubleLinkedList_Node *current = lst->tail;
    for (size_t i = 0; i < index; i++) {
        current = current->prev;
    }
    DoubleLinkedList_deleteNode(lst, current);
    return true;
}

size_t DoubleLinkedList_getNodeIndex(struct DoubleLinkedList *lst,
                                     struct DoubleLinkedList_Node *target) {
    size_t i = 0;
    while (target->next != NULL) {
        i++;
        target = target->next;
    }
    return lst->len - i - 1;
}

struct DoubleLinkedList_Node *
DoubleLinkedList_getByIndex(struct DoubleLinkedList *lst, size_t index) {
    if (index >= lst->len) {
        return NULL;
    }
    struct DoubleLinkedList_Node *current = lst->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}
void DoubleLinkedList_push(struct DoubleLinkedList *lst,
                           struct DoubleLinkedList_Data *data) {
    DoubleLinkedList_insertAfter(lst, lst->tail, data);
}
struct DoubleLinkedList_Data *
DoubleLinkedList_pop(struct DoubleLinkedList *lst) {
    struct DoubleLinkedList_Data *result = lst->tail->d;
    struct DoubleLinkedList_Node *_tail = lst->tail;
    if (lst->tail->prev != NULL) {
        lst->tail->prev->next = NULL;
        lst->tail = lst->tail->prev;
        lst->len--;
    }
    _free(_tail);
    return result;
}
