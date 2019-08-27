#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFunc(void *key, void *value);
unsigned long hashFunc(void *key);
int compareFunc(void *keyA, void *keyB);


int main()
{
    AdtStatus status, size = 100;
    HashTable *hashT;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    forEachFunction forEachF = printFunc;
    void *foundPtr;
    char *foundStr;
    char *key1 = "12345678";
    char *value1 = "12345678";

    char *key2 = "12345678";
    char *value2 = "1234909";
    char *key3 = "67555544478";


    status = hashTableCreate(&hashT, size, hashF, compF);

    status = hashTableInsert(hashT, key1, value1);
    status = hashTableInsert(hashT, key2, value2);
    status = hashTableInsert(hashT, "45679988", "9776756");


    status = hashTableFind(hashT, key1, &foundPtr);
    foundStr = (char*)foundPtr;
    printf("%d\n", status);
    status = hashTableFind(hashT, key2, &foundPtr);
    foundStr = (char*)foundPtr;
    printf("%d\n", status);
    status = hashTableFind(hashT, key3, &foundPtr);
    foundStr = (char*)foundPtr;
    printf("%d\n", status);
    
    status = hashTableForEach(hashT, forEachF);

    return 0;
}

void printFunc(void index, void *key, void *value)
{
    printf("%d", (int*),);
    printf("key = %s, value = %s -> ", (char*)key, (char*)value);
}

unsigned long hashFunc(void *key)
{
    unsigned long hash = 5381;
    int c;
    unsigned char *str = (unsigned char*)key;

    while ((c = *str++) != 0)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int compareFunc(void *keyA, void *keyB)
{
    return strcmp((char*)keyA, (char*)keyB);
}