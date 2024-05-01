#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

#define ENTRY_RESIZE_FACTOR 2
#define ENTRY_INIT_CAPACITY 2

struct HashTable_Key {
    char *str;
};

struct HashTable_Value {
    int n;
};

struct HashTable_Item {
    struct HashTable_Key *key;
    struct HashTable_Value *value;
};

struct TableEntry {

    union {
        struct HashTable_Item *itemLst;
        struct HashTable_Item item;
    } inner;
    size_t len;
    size_t capacity;
};

struct HashTable {
    struct TableEntry *table;
    size_t capacity;
    size_t len;
    size_t mod;
};

unsigned long long HashTable_hash(struct HashTable_Key *data);
void HashTable_destroyKey(struct HashTable_Key *target);
void HashTable_destroyValue(struct HashTable_Value *target);
bool HashTable_keyEquals(struct HashTable_Key *a, struct HashTable_Key *b);
void HashTable_printKey(struct HashTable_Key *key);
void HashTable_printValue(struct HashTable_Value *value);

struct HashTable *HashTable_createTable(size_t mod);
void HashTable_destroyTable(struct HashTable *target);
size_t HashTable_getLen(struct HashTable *target);
// Test itemLst -> item and item -> itemLst
bool HashTable_insert(struct HashTable *target, struct HashTable_Key *key,
                      struct HashTable_Value *value);
// Test itemLst -> item and item -> itemLst
struct HashTable_Value *HashTable_get(struct HashTable *target,
                                      struct HashTable_Key *key);
// Test itemLst -> item and item -> itemLst
bool HashTable_delete(struct HashTable *target, struct HashTable_Key *key);
void HashTable_forEach(struct HashTable *target,
                       void (*f)(struct HashTable_Key *,
                                 struct HashTable_Value *));

void HashTable_printTable(struct HashTable *target);
#endif
