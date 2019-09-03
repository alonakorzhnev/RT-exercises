#ifndef MYMALLOC_H
#define MYMALLOC_H

void* memInit(void *buffer, int size);

void* memAlloc(void *buffer, int size);

void memFree(void *buffer, void *blockPtr);

#endif