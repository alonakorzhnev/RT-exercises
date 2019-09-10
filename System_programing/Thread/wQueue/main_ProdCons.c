#include "wQueue.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>


#define SIZE_QUEUE 3
#define COUNT_PROD 2
#define COUNT_MESSEGES 4
#define COUNT_CONS 3

wQueue *queuePC, *queueCP;

void* produser(void *param)
{
    int i, j, id = *(int*)param;
    char *item;

    item = (char*)malloc(64*sizeof(char));
    
    for(i = 0; i < COUNT_MESSEGES; ++i)
    {  
        strcpy(item, "messege");        
        writeWQueue(queuePC, (void*)item);

        printf("Produser with id = %d sent to consumer %s\n", id, item);                        
    }

    for(j = 0; j < COUNT_MESSEGES; ++j)
    {  
        item = (char*)readWQueue(queueCP);
        printf("Producer with id = %d get from consumer %s\n", id, item);                       
    } 

    pthread_exit(0);   
}

void* consumer(void *param)
{
    char *item;
    int id = *(int*)param;
    pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    while(1) 
    {  
        item = (char*)readWQueue(queuePC);
        printf("Consumer with id = %d get from produser %s\n", id, item);  

        writeWQueue(queueCP, (void*)item); 
        printf("Consumer with id = %d sent to produser %s\n", id, item);               
    }
}

int main()
{    
    pthread_t produsers[COUNT_PROD];
    int prodIndex[COUNT_PROD];

    pthread_t consumers[COUNT_CONS];
    int consIndex[COUNT_CONS];

    int i = 0, j = 0, m = 0, n = 0;

    for(i = 0; i < COUNT_PROD; ++i)
    {
        prodIndex[i] = i;
    }

    for(i = 0; i < COUNT_CONS; ++i)
    {
        consIndex[i] = i;
    }

    queuePC = createWQueue(SIZE_QUEUE);
    queueCP = createWQueue(SIZE_QUEUE);

    for(i = 0; i < COUNT_PROD; ++i)
    {
        pthread_create(&produsers[i], NULL, produser, &prodIndex[i]);
    }

    for(j = 0; j < COUNT_CONS; ++j)
    {
        pthread_create(&consumers[j], NULL, consumer, &consIndex[j]);
    }

    for(m = 0; m < COUNT_PROD; ++m)
    {
        pthread_join(produsers[m], NULL);
    }

    for(n = 0; n < COUNT_CONS; ++n)
    {
        pthread_cancel(consumers[n]);
    }

    /*destroyWQueue(queue);*/
    return 0;
}