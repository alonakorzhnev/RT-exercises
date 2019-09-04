#include "myMalloc.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *buffer, *memory;
    int buffSize = 1000002;

    buffer = (int*)malloc(buffSize);

    memory = (int*)memInit(buffer, buffSize);

    printf("%lu\n", (size_t)memory);
    printf("%x\n", (unsigned int)memory[0]);
   
    memFree(memory);

    return 0;
}