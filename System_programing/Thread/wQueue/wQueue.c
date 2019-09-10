#include "wQueue.h"
#include <semaphore.h>
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>

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
    queue->count = 0;
    queue->read = 0;
    queue->write = 0;
    sem_init(&queue->semEmpty, 0, size);
    sem_init(&queue->semFull, 0, 0);
    pthread_mutex_init(&queue->lock, NULL);

    return queue;                                                                                                                             
}

void* readWQueue(wQueue *queue)
{
    void *readVal;

    sem_wait(&(queue->semFull));
    pthread_mutex_lock(&(queue->lock));

    readVal = queue->arr[queue->read];  
    (queue->read)++;
    
    if(queue->read == queue->size)
    {
        queue->read = 0;
    }

    pthread_mutex_unlock(&(queue->lock));
    sem_post(&(queue->semEmpty));

    return readVal;
}

void writeWQueue(wQueue *queue, void *writeVal)
{
    sem_wait(&(queue->semEmpty));
    pthread_mutex_lock(&(queue->lock));   

    queue->arr[queue->write] = writeVal;    
    (queue->write)++;

    if(queue->write == queue->size)
    {
        queue->write = 0;
    }

    pthread_mutex_unlock(&(queue->lock));
    sem_post(&(queue->semFull));
}

void destroyWQueue(wQueue *queue)
{
    free(queue->arr);
    free(queue);
}


