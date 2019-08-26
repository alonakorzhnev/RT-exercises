#include "hashTable.h"
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

struct HashTable
{
    Node **buskets;
    size_t size;
    hashFunction hashF;
    elementCompare compF;
};

AdtStatus hashTableCreate(HashTable **hashT, size_t size, hashFunction hashF, elementCompare compF)
{
    *hashT = (HashTable*)calloc(1, sizeof(HashTable));    
    if(*hashT == NULL)
    {
        return AllocationError;
    }

    (*hashT)->buskets = (Node**)malloc(size*1.3*sizeof(Node*));
    if((*hashT)->buskets == NULL)
    {
        free(*hashT);
        return AllocationError;
    }

    (*hashT)->size = size*1.3;
    (*hashT)->hashF = hashF;
    (*hashT)->compF = compF;

    return OK;
}

AdtStatus hashTableDestroy(HashTable *hashT, elementDestroy destroyF)
{

    return OK;
}

AdtStatus hashTableInsert(HashTable *hashT, void *key, void *value)
{

    return OK;
}

AdtStatus hashTableFind(HashTable *hashT, void *key, void **value)
{
    
}

static AdtStatus findNodeInBusket(HashTable *hashT, void *key, Node **curr)
{
    unsigned long searchKey;
    AdtStatus status;

    if(hashT == NULL)
    {
        return Nullpointer;
    }

    searchKey = (hashT->(hashF(key)))%(hashT->size);

    if(hashT->baskets[searchKey] == NULL)
    {
        return FreeBusket;
    }
    else
    {
        return findNodeInList(hashT->baskets[searchKey], key, hashT->compF, *curr);
    }
}


AdtStatus hashTableForEach(HashTable *hashT)
{

    return OK;
}

AdtStatus hashTableRemove(HashTable *hashT, void *key, void **value)
{

    return OK;
}