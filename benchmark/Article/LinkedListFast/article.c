#include "LinkedListFast.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDLEN 85

int getWordLower(char **ptrToWord);
void countWords(struct LinkedList *lst);
void printResult(struct LinkedList *lst);

int main(void) {
    freopen("../article.txt", "r", stdin);
    struct LinkedList *lst = LinkedList_createList();
    countWords(lst);
    printResult(lst);
    LinkedList_destroyList(lst);
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
            struct LinkedList_Node *searchResult =
                LinkedList_searchNode(lst, word);
            if (searchResult != NULL) {
                searchResult->count++;
                free(word);
            } else {
                LinkedList_insertFirst(lst, word);
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
        printf("%s %d\n", current->word, current->count);
        current = current->next;
    }
}
