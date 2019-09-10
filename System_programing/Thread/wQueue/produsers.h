#ifndef PRODUSERS_H
#define PRODUSERS_H
#include "wQueue.h"

typedef struct Produser Produser;

void createProdusers(wQueue *queuePC, wQueue *queueCP);

void* produser(void *param);

#endif