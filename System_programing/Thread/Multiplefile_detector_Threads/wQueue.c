#include "wQueue.h"
#include <semaphore.h>
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h>

struct wQueue
{
    void **arr;
    int read;
    int write;
    int size;
    sem_t semEmpty;
    sem_t semFull;
    pthread_mutex_t lock; 
};

int createWQueue(wQueue **queue, int size)
{
    *queue = (wQueue*)malloc(sizeof(wQueue));
    if(queue == NULL)
    {
        return 1;
    }

    (*queue)->arr = (void**)malloc(sizeof(void*)*size);
    if((*queue)->arr == NULL)
    {
        free(*queue);
        return 1;
    }

    (*queue)->size = size;
    (*queue)->read = 0;
    (*queue)->write = 0;
    sem_init(&(*queue)->semEmpty, 0, size);
    sem_init(&(*queue)->semFull, 0, 0);
    pthread_mutex_init(&(*queue)->lock, NULL);

    return 0;                                                                                                                             
}

int readWQueue(wQueue *queue, void **readVal)
{
    if(queue == NULL || readVal == NULL)
    {
        return 1;
    }

    sem_wait(&(queue->semFull));
    pthread_mutex_lock(&(queue->lock));

    *readVal = queue->arr[queue->read];  
    queue->read = (queue->read + 1)%queue->size;

    pthread_mutex_unlock(&(queue->lock));
    sem_post(&(queue->semEmpty));

    return 0;
}

int writeWQueue(wQueue *queue, void *writeVal)
{
    if(queue == NULL || writeVal == NULL)
    {
        return 1;
    }

    sem_wait(&(queue->semEmpty));
    pthread_mutex_lock(&(queue->lock));   

    queue->arr[queue->write] = writeVal;    
    queue->write = (queue->write + 1)%queue->size;

    pthread_mutex_unlock(&(queue->lock));
    sem_post(&(queue->semFull));

    return 0;
}

void destroyWQueue(wQueue *queue)
{
    if(queue == NULL)
    {
        return;
    }

    free(queue->arr);
    free(queue);
}


