#include <stdlib.h>
#include <stdio.h>
#define SET_FREE(header) ((header) & 0x7fffffff)
#define SET_OCCUPIED(header) ((header) | 0x80000000)
#define GET_SIZE(header) ((header) & 0x7fffffff)

static int checkBit(int num)
{
    if((num & 0x80000000) == 0)
        return 0;
    else
        return 1;
}

static void addBlock(int *header, int size)
{
    int oldSize = *header;

    *header = SET_OCCUPIED(size); 

    /*Split blocks*/
    if(size < oldSize)
        *(header + size/4) = oldSize - size;
}

void* memInit(void *buffer, int buffSize)
{
    int bufHead;
    int *header, *end;

    if(buffer == NULL)
    {
        return NULL;
    }

    /*Align size and addresses*/
    bufHead = (4 - ((size_t)buffer)%4)%4;   
    buffer = (char*)buffer + bufHead;
    buffSize = buffSize - bufHead;
    buffSize = buffSize - (buffSize)%4;

    header = (int*)buffer;
    /*Set header*/
    *header = SET_FREE(buffSize - 4);
    end = (int*)&(((char*)buffer)[buffSize - 4]);
    /*Set end of memory*/
    *end = SET_OCCUPIED(0);

    return (void*)buffer;
}

void* memAlloc(void *buffer, int size)
{
    int *header, *next;

    if(buffer == NULL)
    {
        return NULL;
    }

    /*New size + header*/
    size += (4 - size%4)%4 + 4;
    header = (int*)buffer; 

    while(1)
    {
        if(checkBit(*header) == 1)
        {
            /*End of heap - return NULL*/
            if(GET_SIZE(*header) == 0)
                return NULL;
            
            /*Go to next block*/
            header = header + GET_SIZE(*header)/4;
        }
        else
        {
            /*Block size more then size allocation*/
            if(size <= *header)
            {
                addBlock(header, size);
                return header;
            }
            /*Block size less then size allocation*/
            else
            {
                next = header + *header/4;

                /*Merge free blocks*/
                if(checkBit(*next) == 0)
                {
                    *header = *header + *next;
                } 
                else
                {
                    header = next;
                }                                    
            }         
        }        
    }    
}

void memFree(void *block)
{
    int *header = (int*)block, *next;

    *header = SET_FREE(*header);
    next = *header/4 + header;

    /*Merge free blocks*/
    while(checkBit(*next) == 0)
    {
        *header = *header + *next;
        next = *next/4 + next;
    }
}