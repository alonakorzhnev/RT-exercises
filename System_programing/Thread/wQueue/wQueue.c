#include "wQueue.h"
#include <semaphore.h>
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h>

struct wQueue
{
    void **arr;
    int rHead;
    int wTail;
    int size;
    sem_t semEmpty;
    sem_t semFull;
    pthread_mutex_t lock; 
};

wQueue* createWQueue(int size)
{
    wQueue *queue;

    queue = (wQueue*)malloc(sizeof(wQueue));
    if(queue == NULL)
    {
        return NULL;
    }

    queue->arr = (void**)malloc(sizeof(void*)*size);
    if(queue->arr == NULL)
    {
        free(queue);
        return NULL;
    }

    queue->size = size;
    queue->rHead = 0;
    queue->wTail = 0;
    sem_init(&queue->semEmpty, 0, size);
    sem_init(&queue->semFull, 0, 0);
    queue->lock = PTHREAD_MUTEX_INITIALIZER;

    return queue;                                                                                                                             
}

void* readWQueue(wQueue *queue)
{
    void *readVal;

    readVal = queue[queue->rHead];
    queue->rHead = (queue->rHead + 1)%queue->size;

    return readVal;
}

void writeWQueue(wQueue *queue, void *writeVal)
{
    queue[queue->wTail] = writeVal;
    queue->wTail = (queue->wTail + 1)%queue->size;
}

int isEmpty(wQueue *queue)
{
    return (queue->rHead == queue->wTail) ? 1 : 0;
}

int isFull(wQueue *queue)
{
    return ((queue->wTail + 1)%queue->size == queue->rHead) ? 1 : 0;
}

void destroyWQueue(wQueue *queue)
{
    int i;

    if(queue == NULL)
    {
        return;
    }

    for(i = 0; i < queue->size; ++i)
    {
        free(queue->arr[i]);
    }
    free(arr);
    free(queue);
}


