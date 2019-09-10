#ifndef CONSUMERS_H
#define CONSUMERS_H
#include "wQueue.h"

typedef struct Consumer Consumer;

void createConsumers(wQueue *queuePC, wQueue *queueCP);

void* consumer(void *param);

#endif