#include "wQueue.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


#define SIZE_QUEUE 30
#define COUNT_PROD 5
#define COUNT_MESSEGES 10
#define COUNT_CONS 10

wQueue *queue;

void* produser(void *param)
{
    int i;
    char *item;

    item = (char*)malloc(64*sizeof(char));
    

    for(i = 0; i < COUNT_MESSEGES; ++i)
    {
        sem_wait(queue->semEmpty);
        pthread_mutex_lock(&(queue->lock));

        if(!isFull(queue))
        {
            writeWQueue(queue, item);
            pthread_mutex_unlock(&(queue->lock));
            sem_post(queue->semFull);
        }
        else
        {
            pthread_mutex_unlock(&(queue->lock));
        }        
    }
}

void* consumer(void *param)
{
    char item[64];

    while(1) 
    {
        sem_wait(queue->semFull);
        pthread_mutex_lock(&(queue->lock));

        if(!isEmpty(queue))
        {
            item = readWQueue(queue); /*change*/           

            if(item == stopItem)
            {
                writeWQueue(queue, stopItem); 
                pthread_mutex_unlock(&(queue->lock));
                sem_post(queue->semFull);               
                pthread_exit(0);
            }
            pthread_mutex_unlock(&(queue->lock));
            sem_post(queue->semEmpty);
        }
        else
        {
            pthread_mutex_unlock(&(queue->lock));
        }     
    }
}

int main()
{    
    pthread_t produsers[COUNT_PROD];
    pthread_t consumers[COUNT_CONS];
    int i = 0, j = 0, m = 0, n = 0;

    queue = createWQueue(SIZE_QUEUE);

    for(i = 0; i < COUNT_PROD; ++i)
    {
        pthread_create(&produsers[i], NULL, produser, NULL);
    }

    for(j = 0; j < COUNT_CONS; ++j)
    {
        pthread_create(&consumers[j], NULL, consumer, NULL);
    }

    for(m = 0; m < COUNT_PROD; ++m)
    {
        pthread_join(produsers[m], NULL);
    }

    if(!isFull(queue))
    {
        writeWQueue(queue, stopItem);
    }

    for(n = 0; n < COUNT_CONS; ++n)
    {
        pthread_join(consumers[n], NULL);
    }

    destroyWQueue(queue);
    return 0;
}