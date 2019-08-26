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
    void *foundPtr;
    char *foundStr;
    char *key = "12345678";
    char *value = "12345678";

    status = hashTableCreate(&hashT, size, hashF, compF);

    status = hashTableInsert(hashT, key, value);

    status = hashTableFind(hashT, key, &foundPtr);
    foundStr = (char*)foundPtr;
    printf("%d", status);

    return 0;
}

void printFunc(void *key, void *value)
{
    printf("key = %s, value = %s", (char*)key, (char*)value);
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

    /*printf("%lu\n", hash);*/

    return hash;
}

int compareFunc(void *keyA, void *keyB)
{
    char *strA, *strB;

    strA = (char*)keyA;
    strB = (char*)keyB;

    return strcmp(strA, strB);
}