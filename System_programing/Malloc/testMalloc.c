#include "myMalloc.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *buffer, *memory;
    int size = 1000000;

    buffer = (int*)malloc(size);

    memory = (int*)memInit(buffer, size);

    printf("%lu\n", (size_t)memory);

    return 0;
}