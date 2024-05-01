#include "HashTable.h"
#include "trace.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDLEN 85

int getWordLower(char **ptrToWord);
void countWords(struct HashTable *lst);
void printResult(struct HashTable *lst);

void _printData(struct HashTable_Key *key, struct HashTable_Value *value);

int main(void) {
    traceInit();
    freopen("../article.txt", "r", stdin);
    struct HashTable *table = HashTable_createTable(1000639);
    countWords(table);
    printResult(table);

    HashTable_destroyTable(table);
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

void countWords(struct HashTable *table) {
    while (1) {
        char *word = NULL;
        int r = getWordLower(&word);
        if (word != NULL) {
            struct HashTable_Key key = {word};
            struct HashTable_Value *value = HashTable_get(table, &key);
            if (value != NULL) {
                value->n++;
                free(word);
            } else {
                struct HashTable_Value newValue = {1};
                HashTable_insert(table, &key, &newValue);
            }
        } else {
            break;
        }

        if (r == 0) {
            break;
        }
    }
}

void printResult(struct HashTable *table) {
    HashTable_forEach(table, _printData);
}

void _printData(struct HashTable_Key *key, struct HashTable_Value *value) {
    printf("%s %d\n", key->str, value->n);
}

unsigned long long HashTable_hash(struct HashTable_Key *data) {
    unsigned long long result = 0;
    char *s = data->str;
    while (*s != '\0') {
        result = result * 127U + (unsigned long long)*s;
        s++;
    }
    return result;
}
void HashTable_destroyKey(struct HashTable_Key *target) { _free(target); }
void HashTable_destroyValue(struct HashTable_Value *target) { _free(target); }
bool HashTable_keyEquals(struct HashTable_Key *a, struct HashTable_Key *b) {
    if (strcmp(a->str, b->str) == 0) {
        return true;
    } else {
        return false;
    }
}
void HashTable_printKey(struct HashTable_Key *key) {
    putchar('"');
    printf("%s", key->str);
    putchar('"');
}
void HashTable_printValue(struct HashTable_Value *value) {
    printf("%d", value->n);
}
