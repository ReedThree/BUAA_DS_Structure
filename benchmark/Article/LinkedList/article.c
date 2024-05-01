#include "LinkedList.h"
#include "trace.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDLEN 85

int getWordLower(char **ptrToWord);
void countWords(struct LinkedList *lst);
void printResult(struct LinkedList *lst);

int main(void) {
    traceInit();
    freopen("../article.txt", "r", stdin);
    char *initStr = (char *)malloc(sizeof(char));
    initStr[0] = '\0';
    struct LinkedList_Data initData = {initStr, 0};
    struct LinkedList *lst = LinkedList_createList(&initData);
    countWords(lst);
    printResult(lst);
    LinkedList_destroyList(lst);
    traceSummarize();
    traceFree();
    return 0;
}

int getWordLower(char **ptrToWord) {
    char buffer[MAXWORDLEN] = {0};
    int len = 0;
    int ch = 0;
    while (1) {
        ch = getchar();
        if (isalpha(ch)) {
            buffer[len] = (char)tolower(ch);
            len++;
            continue;
        }
        if (ch == EOF) {
            break;
        }
        if (len > 0) {
            break;
        } else {
            continue;
        }
    }
    if (len == 0) {
        return -1;
    }
    *ptrToWord = (char *)malloc((unsigned)(len + 1) * sizeof(char));
    strcpy(*ptrToWord, buffer);
    if (ch != EOF) {
        return 1;
    }
    return 0;
}

void countWords(struct LinkedList *lst) {
    while (1) {
        char *word = NULL;
        int r = getWordLower(&word);
        if (word != NULL) {
            struct LinkedList_Data thisWord = {word, 1};
            struct LinkedList_Node *searchResult =
                LinkedList_searchNode(lst, &thisWord);
            if (searchResult != NULL) {
                searchResult->d->count++;
                free(word);
            } else {
                LinkedList_insertFirst(lst, &thisWord);
            }
        } else {
            break;
        }

        if (r == 0) {
            break;
        }
    }
}

void printResult(struct LinkedList *lst) {
    struct LinkedList_Node *current = lst->head;

    while (current != NULL) {
        printf("%s %d\n", current->d->word, current->d->count);
        current = current->next;
    }
}

void LinkedList_destroyData(struct LinkedList_Data *target) {
    free(target->word);
    free(target);
}
void LinkedList_printData(struct LinkedList_Data *target) {
    printf("{word = \"%s\", count = %d}", target->word, target->count);
}
int LinkedList_dataEquals(struct LinkedList_Data *a,
                          struct LinkedList_Data *b) {
    if (strcmp(a->word, b->word) == 0) {
        return 1;
    } else {
        return 0;
    }
}
int LinkedList_dataCmp(struct LinkedList_Data *a, struct LinkedList_Data *b) {
    return strcmp(a->word, b->word);
}
