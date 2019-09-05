#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *key;
    void *value;
    Node *next;
};

AdtStatus createNode(Node **newNode, void *key, void *value)
{
    *newNode = (Node*)malloc(sizeof(Node));
    if(*newNode == NULL)
    {
        return AllocationError;
    }

    (*newNode)->key = key;
    (*newNode)->value = value;
    (*newNode)->next = NULL;

    return OK;
}

void* getValue(Node *node)
{
    if(node != NULL)
    {
        return node->value;
    }
    return NULL;
}

void setValue(Node *node, void *value)
{
    if(node != NULL && value != NULL)
    {
        node->value = value;
    }
}

void setNext(Node *parent, Node *curr)
{
    if(parent != NULL && curr != NULL)
    {
        parent->next = curr->next;
    }
}

AdtStatus addNode(Node **list, void *key, void *value)
{
    Node *newNode;
    AdtStatus status;

    status = createNode(&newNode, key, value);
    if(status == AllocationError)
    {
        return AllocationError;
    }

    newNode->next = *list;
    *list = newNode;

    return OK;
}

AdtStatus findNodeInList(Node *list, void *key, elementCompare compF, Node **parent, Node **curr)
{
    *parent = NULL;
    
    while(list != NULL)
    {        
        if(compF(key, list->key) == 0)
        {
            *curr = list;
            return IsFound;
        }

        *parent = list;
        list = list->next;
    }

    return IsNotFound;
}

AdtStatus listForEach(Node *head, forEachFunction func, void *context)
{
    Node *temp;
    temp = head;

    if(head == NULL)
    {
        return NullPointer;
    }

    while(temp != NULL)
    {
        func(temp->key, temp->value, context);
        temp = temp->next;
    }
    printf("NULL\n");

    return OK;
}

AdtStatus destroyList(Node *head, elementDestroy destroyF)
{
    Node *temp;
    AdtStatus status = OK;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        if(destroyNode(temp, destroyF) != OK)
        {
            status = Failed;
        }
    }
    return status;
}

AdtStatus destroyNode(Node *node, elementDestroy destroyF) 
{
    if(node == NULL)
    {
        return NullPointer;
    }

    destroyF(node->key, node->value);
    free(node);
    return OK;
}