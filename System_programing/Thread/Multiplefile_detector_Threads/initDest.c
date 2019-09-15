#include "initDest.h"
#include "fileOps.h"
#include <stdlib.h>
#include <string.h>

#define hashSize 100

static unsigned long hashFunc(void *key)
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

static int compareFunc(void *keyA, void *keyB)
{
    if(keyA == NULL || keyB == NULL)
    {
        return -1;
    }

    if(strcmp((char*)keyA, (char*)keyB) == 0)
    {
        return 0;
    }
 
    return -1;
}

static void destroyFunc(void *md5Output, void *pathName)
{
    free(md5Output);
    free(pathName);
}


HashTable* init(char* path){
	HashTable *ht;
	if (path == NULL || !isDir(path))
		return NULL;
	
	if (hashTableCreate(&ht, hashSize, hashFunc, compareFunc) != OK)
		return NULL;
		
	return ht;
	
}


void dest(HashTable* ht){
	hashTableDestroy(ht, destroyFunc);
}