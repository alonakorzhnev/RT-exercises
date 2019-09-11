#ifndef WQUEUE_H
#define WQUEUE_H
#include <semaphore.h>
#include <pthread.h> 
#include <unistd.h> 

typedef struct wQueue wQueue;

int createWQueue(wQueue **queue, int count);

int readWQueue(wQueue *queue, void **readVal);

int writeWQueue(wQueue *queue, void *writeVal);

void destroyWQueue(wQueue *queue);

#endif