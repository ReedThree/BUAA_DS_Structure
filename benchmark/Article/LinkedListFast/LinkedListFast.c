#include "LinkedListFast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList *LinkedList_createList(void) {
    struct LinkedList *result =
        (struct LinkedList *)malloc(sizeof(struct LinkedList));
    result->len = 0;

    result->head = NULL;

    return result;
}

void LinkedList_destroyList(struct LinkedList *lst) {
    struct LinkedList_Node *this = lst->head;
    while (this != NULL) {
        struct LinkedList_Node *next = this->next;
        free(this->word);
        free(this);
        this = next;
    }
    free(lst);
}

void LinkedList_insertFirst(struct LinkedList *lst, char *data) {
    struct LinkedList_Node *newHead =
        (struct LinkedList_Node *)malloc(sizeof(struct LinkedList_Node));

    newHead->word = data;
    newHead->count = 1;
    newHead->next = lst->head;
    lst->head = newHead;
    lst->len++;
}

struct LinkedList_Node *LinkedList_searchNode(struct LinkedList *lst,
                                              char *data) {
    struct LinkedList_Node *this = lst->head;
    while (this != NULL) {
        if (strcmp(this->word, data) == 0) {
            return this;
        }
        this = this->next;
    }
    return NULL;
}
