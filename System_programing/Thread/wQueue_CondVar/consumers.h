#ifndef CONSUMERS_H
#define CONSUMERS_H
#include "wQueue.h"

typedef struct Consumer Consumer;

pthread_t* createConsumers(wQueue *queuePC, wQueue *queueCP);

void* consumer(void *param);

void killConsumers(pthread_t *consumers);

#endif