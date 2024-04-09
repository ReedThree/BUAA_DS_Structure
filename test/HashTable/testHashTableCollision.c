#include "HashTable.h"
#include "trace.h"

#include <stdio.h>
#include <string.h>

unsigned long long ullPow(unsigned long long base, unsigned long long exp);

int main(void) {
    traceInit();

    struct HashTable *table = HashTable_createTable(1000639U);
    printf("%d:%zu\n", 1, HashTable_getLen(table));
    printf("%d:\n", 2);
    HashTable_printTable(table);

    struct HashTable_Key k1 = {(char *)"Scout_1"};
    struct HashTable_Value v1 = {1};

    struct HashTable_Key k2 = {(char *)"Scout_2"};
    struct HashTable_Value v2 = {2};

    struct HashTable_Key k3 = {(char *)"Scout_3"};
    struct HashTable_Value v3 = {3};

    struct HashTable_Key k4 = {(char *)"Scout_4"};
    struct HashTable_Value v4 = {4};

    HashTable_insert(table, &k1, &v1);
    printf("%d:%zu\n", 3, HashTable_getLen(table));
    printf("%d:\n", 4);
    HashTable_printTable(table);

    HashTable_insert(table, &k2, &v2);
    printf("%d:%zu\n", 5, HashTable_getLen(table));
    printf("%d:\n", 6);
    HashTable_printTable(table);

    HashTable_insert(table, &k3, &v3);
    printf("%d:%zu\n", 7, HashTable_getLen(table));
    printf("%d:\n", 8);
    HashTable_printTable(table);

    HashTable_insert(table, &k4, &v4);
    printf("%d:%zu\n", 9, HashTable_getLen(table));
    printf("%d:\n", 10);
    HashTable_printTable(table);

    struct HashTable_Value *rv1 = HashTable_get(table, &k1);
    printf("%d:", 11);
    HashTable_printValue(rv1);
    putchar('\n');
    struct HashTable_Value *rv2 = HashTable_get(table, &k2);
    printf("%d:", 12);
    HashTable_printValue(rv2);
    putchar('\n');
    struct HashTable_Value *rv3 = HashTable_get(table, &k3);
    printf("%d:", 13);
    HashTable_printValue(rv3);
    putchar('\n');
    struct HashTable_Value *rv4 = HashTable_get(table, &k4);
    printf("%d:", 14);
    HashTable_printValue(rv4);
    putchar('\n');

    HashTable_delete(table, &k1);
    printf("%d:%zu\n", 15, HashTable_getLen(table));
    printf("%d:\n", 16);
    HashTable_printTable(table);

    HashTable_delete(table, &k2);
    printf("%d:%zu\n", 17, HashTable_getLen(table));
    printf("%d:\n", 18);
    HashTable_printTable(table);

    HashTable_delete(table, &k3);
    printf("%d:%zu\n", 19, HashTable_getLen(table));
    printf("%d:\n", 20);
    HashTable_printTable(table);

    HashTable_delete(table, &k4);
    printf("%d:%zu\n", 21, HashTable_getLen(table));
    printf("%d:\n", 22);
    HashTable_printTable(table);

    HashTable_destroyTable(table);
    // traceSummarize();
    traceFree();
    return 0;
}

unsigned long long HashTable_hash(struct HashTable_Key *data) {
    unsigned long long result =
        (unsigned)data->str[1] * 127 + (unsigned)data->str[0];
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
    printf("%zu", value->n);
}

inline unsigned long long ullPow(unsigned long long base,
                                 unsigned long long exp) {
    unsigned long long result = 1;
    for (unsigned long long i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}
