#include <stdlib.h>
#include <stdio.h>
#define SET_FREE(header) ((header) & 0x7fffffff)
#define SET_OCCUPIED(header) ((header) | 0x80000000)

static int checkBit(int *num)
{
    if(*num & 0x80000000)
        return 0;
    else
        return 1;
}

static void addBlock(int *header, int size)
{
    int oldSize = *header;

    *header = SET_OCCUPIED(size); 

    if(size < oldSize)
        *(header + size) = oldSize - size;
}

void* memInit(void *buffer, int buffSize)
{
    int bufHead;
    int *header, *end;

    if(buffer == NULL)
    {
        return NULL;
    }

    bufHead = (4 - ((size_t)buffer)%4)%4;   
    buffer = (char*)buffer + bufHead;
    buffSize = buffSize - bufHead;
    buffSize = buffSize - (buffSize)%4;

    header = (int*)buffer;
    *header = SET_FREE(buffSize - 2*4);
    /*header[(buffSize -2*4)/4 - 1] = SET_OCCUPIED(0);*/
    end = (int*)&(((char*)buffer)[buffSize - 2*4]);
    *end = SET_OCCUPIED(0);

    return (void*)buffer;
}

void* memAlloc(void *buffer, int buffSize, int size)
{
    int *header, *buffPtr;
    int currIndex = 0, sizeInt, buffInt;

    if(buffer == NULL)
    {
        return NULL;
    }

    buffPtr = (int*)buffer;
    sizeInt = (size + (4 - size%4) + 4)/4;
    buffInt = buffSize/4;   

    while(currIndex != buffInt)
    {
        *header = buffPtr[currIndex];

        if(checkBit(header))
        {
            currIndex = buffPtr[currIndex];
        }
        else
        {
            if(size <= buffPtr[currIndex])
            {
                addBlock(header, size);
            }
            else
            {
                
            }
            
        }
        
    }
    
}

void memFree(void *block)
{
    int *head = (int*)block, *next;

    *head = SET_FREE(*head);
    next = *head/4 + head;

    while(checkBit(next) == 1)
    {
        *head = *head/4 + *next/4;
        next = *next/4 + next;
    }
}