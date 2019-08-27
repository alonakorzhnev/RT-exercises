#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;
typedef enum {OK, Failed, AllocationError, NullPointer, IsFound, IsNotFound} AdtStatus;
typedef int (*elementCompare)(void *keyA, void *keyB);
typedef void (*forEachFunction)(void *key, void *value, void *context);
typedef void (*elementDestroy)(void *key, void *value);

AdtStatus createNode(Node **newNode, void *key, void *value);

AdtStatus addNode(Node **list, void *key, void *value);

AdtStatus findNodeInList(Node *list, void *key, elementCompare compF, Node **parent, Node **curr);

AdtStatus listForEach(Node *head, forEachFunction func, void *context);

AdtStatus destroyNode(Node *node, elementDestroy destroyF);

AdtStatus destroyList(Node *head, elementDestroy destroyF);

void* getValue(Node *node);

void setValue(Node *node, void *value);

void setNext(Node *parent, Node *curr);

#endif