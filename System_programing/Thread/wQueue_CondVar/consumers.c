#include "consumers.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_CONSUMERS 5

struct Consumer
{
    wQueue *queuePC;
    wQueue *queueCP;
    int id;    
};

void* consumer(void *param)
{
    char *item;
    Consumer *consumer = (Consumer*)param;

    pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    while(1) 
    {  
        item = (char*)readWQueue(consumer->queuePC);
        printf("Consumer with id = %d get from produser %s\n", consumer->id, item);  

        writeWQueue(consumer->queueCP, (void*)item); 
        printf("Consumer with id = %d sent to produser %s\n", consumer->id, item);               
    }
}

pthread_t* createConsumers(wQueue *queuePC, wQueue *queueCP)
{
    pthread_t *consumers;
    int index[COUNT_CONSUMERS];
    int i = 0;
    Consumer *cons;

    consumers = (pthread_t*)malloc(sizeof(pthread_t)*COUNT_CONSUMERS);

    for(i = 0; i < COUNT_CONSUMERS; ++i)
    {
        index[i] = i;
    }

    for(i = 0; i < COUNT_CONSUMERS; ++i)
    {
        cons = (Consumer*)malloc(sizeof(Consumer));
        cons->id = index[i];
        cons->queuePC = queuePC;
        cons->queueCP = queueCP;
        pthread_create(&consumers[i], NULL, consumer, cons);
    }

    return consumers;
}

void killConsumers(pthread_t *consumers)
{
    int i;

    for(i = 0; i < COUNT_CONSUMERS; ++i)
    {
        pthread_cancel(consumers[i]);
    }

    free(consumers);
}
