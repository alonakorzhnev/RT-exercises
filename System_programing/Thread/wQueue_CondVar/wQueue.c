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
    pthread_cond_init(&queue->condEmpty, NULL);
    pthread_cond_init(&queue->condFull, NULL);
    pthread_mutex_init(&queue->lock, NULL);

    return queue;                                                                                                                             
}

void* readWQueue(wQueue *queue)
{
    void *readVal;

    pthread_mutex_lock(&queue->lock);
    while(queue->count == 0)
    {
        pthread_cond_wait(&queue->condFull, &queue->lock);        
    }

    readVal = queue->arr[queue->read];  
    (queue->read)++;
    (queue->count)--;
    
    if(queue->read == queue->size)
    {
        queue->read = 0;
    }
    
    pthread_cond_signal(&queue->condEmpty);
    pthread_mutex_unlock(&(queue->lock));
    return readVal;
}

void writeWQueue(wQueue *queue, void *writeVal)
{
    pthread_mutex_lock(&(queue->lock));  
    while(queue->count == queue->size)
    {
        pthread_cond_wait(&queue->condEmpty, &queue->lock);        
    } 

    queue->arr[queue->write] = writeVal;    
    (queue->write)++;
    (queue->count)++;

    if(queue->write == queue->size)
    {
        queue->write = 0;
    }

    pthread_cond_signal(&queue->condFull);
    pthread_mutex_unlock(&(queue->lock));
}

void destroyWQueue(wQueue *queue)
{
    free(queue->arr);
    free(queue);
}


