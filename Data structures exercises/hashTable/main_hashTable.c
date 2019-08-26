#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFunc(void *key, void *value);
unsigned long hash(unsigned char *str);


int main()
{

    return 0;
}

void printFunc(void *key, void *value)
{
    printf("key = %s, value = %s", (char*)key, (char*)value);
}

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int compareFunc(void *keyA, void *keyB)
{
    char *strA, *strB;

    strA = (char*)keyA;
    strB = (char*)keyB;
    return strcmp(strA, strB);
}