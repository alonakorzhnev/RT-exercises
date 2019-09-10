#include "wQueue.h"
#include "produsers.h"
#include "consumers.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define SIZE_QUEUE 5

int main()
{    
    pthread_t *produsers, *consumers;
    wQueue *queuePC, *queueCP;
    
    queuePC = createWQueue(SIZE_QUEUE);
    queueCP = createWQueue(SIZE_QUEUE);

    produsers = createProdusers(queuePC, queueCP);
    consumers = createConsumers(queuePC, queueCP);

    joinProdusers(produsers);
    killConsumers(consumers);

    /*destroyWQueue(queue);*/
    return 0;
}