#include "produsers.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_MESSEGES 3
#define COUNT_PRODUSERS 5

struct Produser
{
    wQueue *queuePC;
    wQueue *queueCP;
    int id;    
};

void* produser(void *param)
{
    int i;
    char *item;
    Produser *produser = (Produser*)param;

    
    
    for(i = 0; i < COUNT_MESSEGES; ++i)
    {  
        item = (char*)malloc(64*sizeof(char));
        strcpy(item, "messege");        
        writeWQueue(produser->queuePC, (void*)item);

        printf("Produser with id = %d sent to consumer %s\n", produser->id, item);                        
    }

    for(i = 0; i < COUNT_MESSEGES; ++i)
    {  
        item = (char*)readWQueue(produser->queueCP);
        printf("Producer with id = %d get from consumer %s\n", produser->id, item);                    
    } 

    pthread_exit(0);   
}

pthread_t* createProdusers(wQueue *queuePC, wQueue *queueCP)
{
    pthread_t *produsers;
    int index[COUNT_PRODUSERS];
    int i = 0;
    Produser *prod;

    produsers = (pthread_t*)malloc(sizeof(pthread_t)*COUNT_PRODUSERS);

    for(i = 0; i < COUNT_PRODUSERS; ++i)
    {
        index[i] = i;
    }

    for(i = 0; i < COUNT_PRODUSERS; ++i)
    {
        prod = (Produser*)malloc(sizeof(Produser));
        prod->id = index[i];
        prod->queuePC = queuePC;
        prod->queueCP = queueCP;
        pthread_create(&produsers[i], NULL, produser, prod);
    }

    return produsers;
}

void joinProdusers(pthread_t *produsers)
{
    int i;

    for(i = 0; i < COUNT_PRODUSERS; ++i)
    {
        pthread_join(produsers[i], NULL);
    }

    free(produsers);
}