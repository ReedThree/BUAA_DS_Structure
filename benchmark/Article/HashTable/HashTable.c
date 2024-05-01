#include "HashTable.h"
#include "trace.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void HashTable_entryInsert(struct TableEntry *entry,
                           struct HashTable_Item item);
void HashTable_entryDelete(struct TableEntry *entry, size_t idx);
void _printTable(struct HashTable_Key *key, struct HashTable_Value *value);

struct HashTable *HashTable_createTable(size_t mod) {
    struct HashTable *result =
        (struct HashTable *)_malloc(sizeof(struct HashTable));
    result->mod = mod;
    result->capacity = mod;
    result->len = 0;
    result->table =
        (struct TableEntry *)_malloc(mod * sizeof(struct TableEntry));
    for (size_t i = 0; i < mod; i++) {
        result->table[i].len = 0;
        result->table[i].capacity = 0;
    }
    return result;
}
void HashTable_destroyTable(struct HashTable *target) {
    for (size_t i = 0; i < target->capacity; i++) {
        struct TableEntry current = target->table[i];
        if (current.len > 0) {
            if (current.len == 1) {
                HashTable_destroyKey(current.inner.item.key);
                HashTable_destroyValue(current.inner.item.value);
            } else {
                for (size_t j = 0; j < current.len; j++) {
                    HashTable_destroyKey(current.inner.itemLst[j].key);
                    HashTable_destroyValue(current.inner.itemLst[j].value);
                }
                _free(current.inner.itemLst);
            }
        }
    }
    _free(target->table);
    _free(target);
}
inline size_t HashTable_getLen(struct HashTable *target) { return target->len; }
bool HashTable_insert(struct HashTable *target, struct HashTable_Key *key,
                      struct HashTable_Value *value) {
    size_t entryIdx = HashTable_hash(key) % target->mod;
    struct TableEntry *targetEntry = &target->table[entryIdx];

    struct HashTable_Key *_key =
        (struct HashTable_Key *)_malloc(sizeof(struct HashTable_Key));
    memcpy(_key, key, sizeof(struct HashTable_Key));

    struct HashTable_Value *_value =
        (struct HashTable_Value *)_malloc(sizeof(struct HashTable_Value));
    memcpy(_value, value, sizeof(struct HashTable_Value));

    struct HashTable_Item item = {_key, _value};

    if (targetEntry->len == 0) {
        targetEntry->len = 1;
        targetEntry->capacity = 1;
        targetEntry->inner.item = item;
    } else if (targetEntry->len == 1) {
        struct HashTable_Item prev = targetEntry->inner.item;
        if (HashTable_keyEquals(prev.key, _key)) {
            return false;
        } else {
            targetEntry->inner.itemLst = (struct HashTable_Item *)_malloc(
                ENTRY_INIT_CAPACITY * sizeof(struct HashTable_Item));
            targetEntry->inner.itemLst[0].key = prev.key;
            targetEntry->inner.itemLst[0].value = prev.value;
            targetEntry->inner.itemLst[1].key = _key;
            targetEntry->inner.itemLst[1].value = _value;
            targetEntry->len = 2;
            targetEntry->capacity = ENTRY_INIT_CAPACITY;
        }

    } else {
        for (size_t i = 0; i < targetEntry->len; i++) {
            if (HashTable_keyEquals(targetEntry->inner.itemLst[i].key, _key)) {
                return false;
            }
        }
        HashTable_entryInsert(targetEntry, item);
    }
    target->len++;
    return true;
}
struct HashTable_Value *HashTable_get(struct HashTable *target,
                                      struct HashTable_Key *key) {
    size_t entryIdx = HashTable_hash(key) % target->mod;
    if (target->table[entryIdx].len == 0) {
        return NULL;
    } else if (target->table[entryIdx].len == 1) {
        if (HashTable_keyEquals(target->table[entryIdx].inner.item.key, key)) {
            return target->table[entryIdx].inner.item.value;
        } else {
            return NULL;
        }
    } else {
        for (size_t i = 0; i < target->table[entryIdx].len; i++) {
            if (HashTable_keyEquals(
                    target->table[entryIdx].inner.itemLst[i].key, key)) {
                return target->table[entryIdx].inner.itemLst[i].value;
            }
        }
        return NULL;
    }
}
bool HashTable_delete(struct HashTable *target, struct HashTable_Key *key) {
    size_t entryIdx = HashTable_hash(key) % target->mod;
    if (target->table[entryIdx].len == 0) {
        return false;
    } else if (target->table[entryIdx].len == 1) {
        if (!HashTable_keyEquals(target->table[entryIdx].inner.item.key, key)) {
            return false;
        }
        HashTable_destroyKey(target->table[entryIdx].inner.item.key);
        HashTable_destroyValue(target->table[entryIdx].inner.item.value);
        target->table[entryIdx].len = 0;
        target->table[entryIdx].capacity = 0;
        target->len--;
        return true;
    } else if (target->table[entryIdx].len == 2) {
        struct HashTable_Item prev;
        for (size_t i = 0; i < target->table[entryIdx].len; i++) {
            if (HashTable_keyEquals(
                    target->table[entryIdx].inner.itemLst[i].key, key)) {
                HashTable_destroyKey(
                    target->table[entryIdx].inner.itemLst[i].key);
                HashTable_destroyValue(
                    target->table[entryIdx].inner.itemLst[i].value);

                if (i == 0) {
                    prev.key = target->table[entryIdx].inner.itemLst[1].key;
                    prev.value = target->table[entryIdx].inner.itemLst[1].value;
                } else {
                    prev.key = target->table[entryIdx].inner.itemLst[0].key;
                    prev.value = target->table[entryIdx].inner.itemLst[0].value;
                }

                _free(target->table[entryIdx].inner.itemLst);

                target->table[entryIdx].inner.item.key = prev.key;
                target->table[entryIdx].inner.item.value = prev.value;

                target->table[entryIdx].len = 1;
                target->table[entryIdx].capacity = 1;

                target->len--;
                return true;
            }
        }
        return false;
    } else {
        for (size_t i = 0; i < target->table[entryIdx].len; i++) {
            if (HashTable_keyEquals(
                    target->table[entryIdx].inner.itemLst[i].key, key)) {
                HashTable_entryDelete(&target->table[entryIdx], i);
                target->len--;
                return true;
            }
        }
        return false;
    }
}
void HashTable_forEach(struct HashTable *target,
                       void (*f)(struct HashTable_Key *,
                                 struct HashTable_Value *)) {
    for (size_t i = 0; i < target->capacity; i++) {
        if (target->table[i].len > 0) {
            if (target->table[i].len == 1) {
                f(target->table[i].inner.item.key,
                  target->table[i].inner.item.value);
            } else {
                for (size_t j = 0; j < target->table[i].len; j++) {
                    f(target->table[i].inner.itemLst[j].key,
                      target->table[i].inner.itemLst[j].value);
                }
            }
        }
    }
}

void HashTable_printTable(struct HashTable *target) {
    HashTable_forEach(target, _printTable);
}

void HashTable_entryInsert(struct TableEntry *entry,
                           struct HashTable_Item item) {
    if (entry->len >= entry->capacity) {
        entry->capacity *= ENTRY_RESIZE_FACTOR;
        entry->inner.itemLst = (struct HashTable_Item *)_realloc(
            entry->inner.itemLst,
            entry->capacity * sizeof(struct HashTable_Item));
    }

    entry->inner.itemLst[entry->len] = item;
    entry->len++;
}

void HashTable_entryDelete(struct TableEntry *entry, size_t idx) {
    HashTable_destroyKey(entry->inner.itemLst[idx].key);
    HashTable_destroyValue(entry->inner.itemLst[idx].value);
    for (size_t i = idx; i < (entry->len - 1); i++) {
        entry->inner.itemLst[i] = entry->inner.itemLst[i + 1];
    }
    entry->len--;
}

void _printTable(struct HashTable_Key *key, struct HashTable_Value *value) {
    HashTable_printKey(key);
    printf(": ");
    HashTable_printValue(value);
    putchar('\n');
}
