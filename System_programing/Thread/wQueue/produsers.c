#include "produsers.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_MESSEGES 3

struct Produser
{
    wQueue *queuePC;
    wQueue *queueCP;
    int id;    
};

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