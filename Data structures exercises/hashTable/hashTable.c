#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

struct HashTable
{
    Node **baskets;
    size_t size;
    hashFunction hashF;
    elementCompare compF;
};

static AdtStatus findNodeInBusket(HashTable *hashT, void *key, Node **curr);

AdtStatus hashTableCreate(HashTable **hashT, size_t size, hashFunction hashF, elementCompare compF)
{
    *hashT = (HashTable*)calloc(1, sizeof(HashTable));    
    if(*hashT == NULL)
    {
        return AllocationError;
    }

    (*hashT)->baskets = (Node**)malloc(size*1.3*sizeof(Node*));
    if((*hashT)->baskets == NULL)
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
    AdtStatus status;
    void *foundValue;
    unsigned long searchKey;
    Node *newNode;

    status = hashTableFind(hashT, key, &foundValue);

    if(status == NullPointer)
    {
        return NullPointer;
    }
    if(status == FreeBusket)
    {
        searchKey = (hashT->hashF(key))%(hashT->size);
        status = createNode(&newNode, key, value);
        hashT->baskets[searchKey] = newNode;
    }

    return OK;
}

AdtStatus hashTableFind(HashTable *hashT, void *key, void **foundValue)
{   
    Node *foundNode;
    AdtStatus status;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    status = findNodeInBusket(hashT, key, &foundNode);
    return status; 
}

static AdtStatus findNodeInBusket(HashTable *hashT, void *key, Node **curr)
{
    unsigned long searchKey;
    AdtStatus status;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    searchKey = (hashT->hashF(key))%(hashT->size);

    /*printf("%lu\n", searchKey);*/

    if(hashT->baskets[searchKey] == NULL)
    {
        return FreeBusket;
    }
    else
    {
        status = findNodeInList(hashT->baskets[searchKey], key, hashT->compF, curr);
    }

    return status;
}


AdtStatus hashTableForEach(HashTable *hashT)
{

    return OK;
}

AdtStatus hashTableRemove(HashTable *hashT, void *key, void **value)
{

    return OK;
}