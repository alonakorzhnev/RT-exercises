#include "consumers.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>

struct Consumer
{
    wQueue *queuePC;
    wQueue *queueCP;
    int id;    
};

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
