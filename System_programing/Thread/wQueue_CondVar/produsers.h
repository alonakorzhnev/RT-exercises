#ifndef PRODUSERS_H
#define PRODUSERS_H
#include "wQueue.h"

typedef struct Produser Produser;

pthread_t* createProdusers(wQueue *queuePC, wQueue *queueCP);

void* produser(void *param);

void joinProdusers(pthread_t *produsers);

#endif