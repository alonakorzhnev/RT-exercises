#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

struct HashTable
{
    Node **baskets;
    size_t size;
    hashFunction hashF;
    elementCompare compF;
    size_t countElements;
};

static AdtStatus findNodeInBasket(HashTable *hashT, void *key, Node **parent, Node **curr);

AdtStatus hashTableCreate(HashTable **hashT, size_t size, hashFunction hashF, elementCompare compF)
{
    if(size <= 0)
    {
        return Failed;
    }

    *hashT = (HashTable*)malloc(sizeof(HashTable));    
    if(*hashT == NULL)
    {
        return AllocationError;
    }

    (*hashT)->baskets = (Node**)calloc(size*1.3, sizeof(Node*));
    if((*hashT)->baskets == NULL)
    {
        free(*hashT);
        return AllocationError;
    }

    (*hashT)->size = size*1.3;
    (*hashT)->hashF = hashF;
    (*hashT)->compF = compF;
    (*hashT)->countElements = 0;

    return OK;
}

AdtStatus hashTableDestroy(HashTable *hashT, elementDestroy destroyF)
{
    int i;
    AdtStatus status = OK;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    for(i = 0; i < hashT->size; ++i)
    {
        if(destroyList(hashT->baskets[i], destroyF) != OK)    
        {
            status = Failed;
        }  
    }

    free(hashT->baskets);
    free(hashT);
    return status;
}

AdtStatus hashTableInsert(HashTable *hashT, void *key, void *value)
{
    AdtStatus status;
    unsigned long basketIndex;
    Node *foundNode, *parent;

    if(hashT == NULL || key == NULL || value == NULL)
    {
        return NullPointer;
    }

    status = findNodeInBasket(hashT, key, &parent, &foundNode);

    if(status == NullPointer)
    {
        return NullPointer;
    }
    
    if(status == IsNotFound)
    {
        basketIndex = (hashT->hashF(key))%(hashT->size);
        if(addNode(&(hashT->baskets[basketIndex]), key, value) == OK)
        {
            ++(hashT->countElements);
            status = OK;
        }
        else
        {
            status = Failed;
        }        
    }
    
    return status;
}

AdtStatus hashTableUpdate(HashTable *hashT, void *key, void *value)
{
    AdtStatus status;
    Node *foundNode, *parent;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    status = findNodeInBasket(hashT, key, &parent, &foundNode);

    if(status == NullPointer)
    {
        return NullPointer;
    }
    
    if(status == IsFound)
    {
        setValue(foundNode, value);
        status = OK;
    }
    
    return status;
}

AdtStatus hashTableFind(HashTable *hashT, void *key, void **foundValue)
{   
    Node *foundNode, *parent;
    AdtStatus status;

    if(hashT == NULL || key == NULL)
    {
        return NullPointer;
    }

    status = findNodeInBasket(hashT, key, &parent, &foundNode);

    if(status == IsFound)
    {
        *foundValue = getValue(foundNode);
    }

    return status;
}

static AdtStatus findNodeInBasket(HashTable *hashT, void *key, Node **parent, Node **curr)
{
    unsigned long basketIndex;

    if(hashT == NULL || key == NULL)
    {
        return NullPointer;
    }

    basketIndex = (hashT->hashF(key))%(hashT->size);
    return findNodeInList(hashT->baskets[basketIndex], key, hashT->compF, parent, curr);
}


AdtStatus hashTableForEach(HashTable *hashT, forEachFunction func, void *context)
{
    int i;

    if(hashT == NULL)
    {
        return NullPointer;
    }

    for(i = 0; i < hashT->size; ++i)
    {
        listForEach(hashT->baskets[i], func, context);
    }    

    return OK;
}

AdtStatus hashTableRemove(HashTable *hashT, void *key, void **foundValue, elementDestroy destroyF)
{
    Node *foundNode, *parent;
    AdtStatus status;
    unsigned long basketIndex;

    if(hashT == NULL || key == NULL)
    {
        return NullPointer;
    }

    status = findNodeInBasket(hashT, key, &parent, &foundNode);

    if(status == IsFound)
    {
        *foundValue = getValue(foundNode);       

        if(parent == NULL)
        {            
            basketIndex = (hashT->hashF(key))%(hashT->size);
            hashT->baskets[basketIndex] = NULL;
        }
        else
        {
            setNext(parent, foundNode);
        }
        if(destroyNode(foundNode, destroyF) == OK)
        {
            --(hashT->countElements);
            status = OK;
        }
        else
        {
            status = Failed;
        }
    }    

    return status;
}