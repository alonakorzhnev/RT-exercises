#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;
typedef enum {OK, AllocationError, NullPointer, IsFound, IsNotFound, FreeBusket} AdtStatus;
typedef int (*elementCompare)(void *keyA, void *keyB);
typedef void (*forEachFunction)(void *keyA, void *keyB);

AdtStatus createNode(Node **newNode, void *key, void *value);

AdtStatus addNode(Node **list, void *key, void *value);

AdtStatus findNodeInList(Node *list, void *key, elementCompare compF, Node **parent, Node **curr);

AdtStatus printList(Node *head, forEachFunction func);

AdtStatus destroyNode(Node *node);

#endif