#ifndef WQUEUE_H
#define WQUEUE_H

typedef struct wQueue wQueue;

wQueue* createWQueue(int count);

void readWQueue(wQueue *queue, void **readM);

void writeWQueue(wQueue *queue, void *writeM);

#endif