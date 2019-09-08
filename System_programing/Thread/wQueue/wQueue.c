#include "wQueue.h"
#include <semaphore.h>
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h>

struct wQueue
{
    void **arr;
    int head;
    int tail;
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
    queue->head = 0;
    queue->tail = 0;
    sem_init(&queue->semEmpty, 0, size);
    sem_init(&queue->semFull, 0, size);
    pthread_mutex_init(&(queue->lock), NULL);

    return queue;                                                                                                                             
}

void readWQueue(wQueue *queue, void **readM);

void writeWQueue(wQueue *queue, void *writeM);


