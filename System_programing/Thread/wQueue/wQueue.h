#ifndef WQUEUE_H
#define WQUEUE_H

typedef struct wQueue wQueue;

wQueue* createWQueue(int count);

void* readWQueue(wQueue *queue);

void writeWQueue(wQueue *queue, void *writeVal);

int isEmpty(wQueue *queue);

int isFull(wQueue *queue);

void destroyWQueue(wQueue *queue);

#endif