#include "findDup.h"
#include "fileOps.h"
#include "md5.h"
#include "hashTable.h"
#include "initDest.h"
#include "wQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMBER_OF_CONSUMERS 20

struct ProdSt{
    char* path;
    wQueue* wq;
    pthread_t* prodPthread;
};

struct ConsSt{
    wQueue* wq;
    HashTable* ht;
    pthread_mutex_t* printMut;
    pthread_t* consPthread;
};

static void fileScan(char* path, wQueue* wq)
{
    char **content;
    int index = 0;

    content = getContent(path);

    while(content[index] != NULL)
    {        
        if(isFile(content[index]))
        {
            writeWQueue(wq, content[index]);
        }
        else if(isDir(content[index]))
        {
            fileScan(content[index], wq);
            free(content[index]);
        }
        ++index;
    }
}    

static void* producer(void* prodVoid){
    char* path;
    wQueue* wq;
    ProdSt* prod = (ProdSt*)prodVoid;

    wq = prod->wq;
    path = prod->path;

    fileScan(path, wq);
}

static void* consumer(void* consVoid){
    ConsSt* cons = (ConsSt*) consVoid;
    wQueue* wq = cons->wq;
    HashTable* ht = cons->ht;
    unsigned char* md5Out;
    void* pathVoid;
    char* path;
    int status;

    readWQueue(wq, &pathVoid);
    path = (char*)pathVoid;
    md5Out = file2md5(path);

    status = hashTableInsert(ht, md5Out, pathVoid);
    if(status != 0)
    {                
        if(status == 4)
        {
            hashTableFind(ht, md5Out, &pathVoid);
            pthread_mutex_lock(cons->printMut);
            printf("File %s already exists in %s\n", path, (char*)pathVoid);
            pthread_mutex_unlock(cons->printMut);
        }
        free(md5Out);
        free(path);
    }

}

static void createProducer(ProdSt* prod){
    prod->prodPthread = malloc(sizeof(pthread_t));
    pthread_create(prod->prodPthread, NULL, producer, prod);
}

static void createConsumers(ConsSt* cons){
    int i;
    cons->consPthread = malloc(sizeof(pthread_t) * NUMBER_OF_CONSUMERS);
    for (i=0; i<NUMBER_OF_CONSUMERS; i++){
         pthread_create(cons->consPthread + i, NULL, consumer, cons);
    }

}

void findDup(char* path)
{
    ProdSt* prod = (ProdSt*)malloc(sizeof(ProdSt));
    ConsSt* cons = (ConsSt*)malloc(sizeof(ConsSt));
    int initStatus;

    initStatus = init(&prod, &cons, path);
    if(initStatus != 0)
    {
        return;
    }

    createProducer(prod);
    createConsumers(cons);

    dest(prod, cons);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
        return 1;

    findDup(argv[1]);
    return 0;
}