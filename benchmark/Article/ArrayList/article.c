#include "ArrayList.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORDLEN 85

int getWordLower(char **ptrToWord);
void countWords(struct ArrayList *lst);
void printResult(struct ArrayList *lst);

int main(void) {
    freopen("../article_random.txt", "r", stdin);
    struct ArrayList *lst = createList(100);
    countWords(lst);
    printResult(lst);
    destroyList(lst);
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

void countWords(struct ArrayList *lst) {
    while (1) {
        char *word = NULL;
        int r = getWordLower(&word);
        if (word != NULL) {
            struct Data thisWord = {word, 1};
            struct Data *searchResult = listSearchOrdered(lst, &thisWord);
            if (searchResult != NULL) {
                searchResult->count++;
                free(word);
            } else {
                listInsertItemOrdered(lst, thisWord);
            }
        } else {
            break;
        }

        if (r == 0) {
            break;
        }
    }
}

void printResult(struct ArrayList *lst) {
    for (int i = 0; i < lst->len; i++) {
        printf("%s %d\n", lst->lst[i]->word, lst->lst[i]->count);
    }
}

void destroyData(struct Data *target) {
    _free(target->word);
    _free(target);
}
void printData(struct Data *target) {
    printf("{word = \"%s\", count = %d}", target->word, target->count);
}
int dataEquals(struct Data *a, struct Data *b) {
    if (strcmp(a->word, b->word) == 0) {
        return 1;
    } else {
        return 0;
    }
}
int dataCmp(const void *a, const void *b) {
    struct Data *dA = *((struct Data **)a);
    struct Data *dB = *((struct Data **)b);
    return strcmp(dA->word, dB->word);
}
