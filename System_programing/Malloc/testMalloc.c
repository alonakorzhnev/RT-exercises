#include "myMalloc.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *buffer, *memory, *ptr1, *ptr2, *ptr3, *ptr4;
    int buffSize = 150;

    buffer = (int*)malloc(buffSize);

    memory = (int*)memInit(buffer, buffSize);

    printf("%lu\n", (size_t)memory);
    printf("%x\n", (unsigned int)memory[0]);

    ptr1 = (int*)memAlloc(memory, 40);
    ptr2 = (int*)memAlloc(memory, 63);

    printf("%lu\n", (size_t)ptr1);
    printf("%lu\n", (size_t)ptr2);

    /*printf("%x\n", (unsigned int)ptr1[0]);
    printf("%x\n", (unsigned int)ptr2[0]);*/

    memFree(ptr1);

    ptr3 = (int*)memAlloc(memory, 20);
    ptr4 = (int*)memAlloc(memory, 10);
    /*printf("%x\n", (unsigned int)ptr3[0]);*/
    printf("%lu\n", (size_t)ptr3);
    printf("%lu\n", (size_t)ptr4);

    memFree(ptr4);
    memFree(ptr3);

    ptr4 = (int*)memAlloc(memory, 70);
    /*printf("%x\n", (unsigned int)ptr4[0]);*/
    
    printf("%lu\n", (size_t)ptr4);



    return 0;
}