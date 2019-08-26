#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;
typedef enum {OK, AllocationError, NullPointer, IsFound, IsNotFound} AdtStatus;
typedef void (*printFunc)(void *key, void *value);
typedef int (*elementCompare)(void *keyA, void *keyB);

AdtStatus createNode(Node **newNode, void *key, void *value);

AdtStatus addNode(Node *list, Node *newNode);

AdtStatus findNodeInList(Node *list, void *key, elementCompare compF, Node **curr);

AdtStatus printList(Node *head, printFunc func);

AdtStatus destroyNode(Node *node);

#endif