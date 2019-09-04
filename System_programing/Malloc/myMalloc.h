#ifndef MYMALLOC_H
#define MYMALLOC_H

void* memInit(void *buffer, int buffSize);

void* memAlloc(void *buffer, int buffSize, int size);

void memFree(void *blockPtr);

#endif