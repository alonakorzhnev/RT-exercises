#include <stdlib.h>
#include <stdio.h>
#define SET_FREE(header) ((header) & 0x7fffffff)
#define SET_OCCUPIED(header) ((header) | 0x80000000)

void* memInit(void *buffer, int size)
{
    int bufHead;
    unsigned int *intPtr;

    if(buffer == NULL)
    {
        return NULL;
    }

    bufHead = (4 - ((size_t)buffer)%4)%4;   
    buffer = (char*)buffer + bufHead;
    size -= bufHead;
    size -= (size)%4;

    intPtr = (unsigned int*)buffer;
    *intPtr = SET_FREE(size);    

    return (void*)buffer;
}

void* memAlloc(void *buffer, int size)
{

}

void memFree(void *buffer, void *blockPtr)
{

}