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

AdtStatus addNode(Node **list, void *key, void *value)
{
    Node *newNode;
    AdtStatus status;

    if(list == NULL)
    {
        return NullPointer;
    }

    status = createNode(&newNode, key, value);
    if(status == AllocationError)
    {
        return AllocationError;
    }

    newNode->next = *list;
    *list = newNode;

    return OK;
}

AdtStatus findNodeInList(Node *list, void *key, elementCompare compF, Node **curr)
{
    if(list == NULL)
    {
        return NullPointer;
    }
    
    while(list != NULL)
    {        
        if(compF(key, list->key) == 0)
        {
            *curr = list;
            return IsFound;
        }

        list = list->next;
    }

    return IsNotFound;
}

AdtStatus printList(Node *head, elementPrint func)
{
    Node *temp;
    temp = head;

    if(head == NULL)
    {
        return NullPointer;
    }

    while(temp != NULL)
    {
        func(temp->key, temp->value);
        temp = temp->next;
    }

    printf("%s", "NULL\n");
    return OK;
}

AdtStatus destroyNode(Node *node) /*change*/
{
    if(node == NULL)
    {
        return NullPointer;
    }
    free(node);
    return OK;
}