#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h>

typedef struct HashTable HashTable;
typedef unsigned long (*hashFunction)(void *key);
typedef void (*forEachFunction)(void *keyA, void *keyB);
typedef int (*elementCompare)(void *keyA, void *keyB);
typedef void (*elementDestroy)(void *key, void *context);
typedef enum {OK, AllocationError, NullPointer, IsFound, IsNotFound, FreeBusket} AdtStatus;

AdtStatus hashTableCreate(HashTable **hashT, size_t size, hashFunction hashF, elementCompare compF);

AdtStatus hashTableDestroy(HashTable *hashT, elementDestroy destroyF);

AdtStatus hashTableInsert(HashTable *hashT, void *key, void *value);

AdtStatus hashTableFind(HashTable *hashT, void *key, elementCompare compF, Node *curr);

AdtStatus hashTableForEach(HashTable *hashT);

AdtStatus hashTableRemove(HashTable *hashT, void *key, void **value);

#endif