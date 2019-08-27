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

static AdtStatus findNodeInBasket(HashTable *hashT, void *key, Node **parent, Node **curr);

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
    unsigned long basketIndex;
    Node *newNode;

    status = hashTableFind(hashT, key, &foundValue);

    if(status == NullPointer)
    {
        return NullPointer;
    }
    else
    {
        basketIndex = (hashT->hashF(key))%(hashT->size);
        status = addNode(&(hashT->baskets[basketIndex]), key, value);
    }

    return status;
}

AdtStatus hashTableFind(HashTable *hashT, void *key, void **foundValue)
{   
    Node *foundNode, *parent;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    return findNodeInBasket(hashT, key, &parent, &foundNode);
}

static AdtStatus findNodeInBasket(HashTable *hashT, void *key, Node **parent, Node **curr)
{
    unsigned long basketIndex;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    basketIndex = (hashT->hashF(key))%(hashT->size);
    return findNodeInList(hashT->baskets[basketIndex], key, hashT->compF, parent, curr);
}


AdtStatus hashTableForEach(HashTable *hashT, forEachFunction func)
{
    int i;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    for(i = 0; i < hashT->size; ++i)
    {
        printList(hashT->baskets[i], func);
    }

    return OK;
}

AdtStatus hashTableRemove(HashTable *hashT, void *key, void **value)
{

    return OK;
}