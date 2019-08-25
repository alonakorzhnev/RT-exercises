#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
struct Node
{
    Node *left;
    Node *right;
    int value;
};

struct Tree
{
    Node *root;
};

static void inOrder(Node *root, walkFunc func);
static void postOrder(Node *root, walkFunc func);
static void preOrder(Node *root, walkFunc func);

Tree* createTree()
{
    Tree *treePtr = (Tree*)malloc(sizeof(Tree));

    if(treePtr == NULL)
    {
        return NULL;
    }

    treePtr->root = NULL;
    return treePtr;    
}

static Node* createNode(int value)
{
    Node *nodePtr;

    nodePtr = (Node*)malloc(sizeof(Node));
    if(nodePtr == NULL)
    {
        return NULL;
    }

    nodePtr->value = value;
    nodePtr->left = NULL;
    nodePtr->right = NULL;

    return nodePtr;
}

int insertNode(Tree *tree, int value)
{
    Node *newNode, *curr, *parent;

    if(tree == NULL)
    {
        return 1;
    }   

    newNode = createNode(value);

    if(newNode == NULL)
    {
        return 1;
    }

    curr = tree->root;
    parent = NULL;

    if(curr == NULL)
    {
        tree->root = newNode;
        return 0;
    }

    while(curr != NULL)
    {
        parent = curr;
        if(value < curr->value)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    
    if(value < parent->value)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    return 0;
}

int searchNode(Tree *tree, int value)
{
    Node *curr, *parent;
    int result = 0;

    if(tree == NULL)
    {
        return 0;
    }  

    curr = tree->root;
    parent = NULL;

    if(curr == NULL)
    {
        return 0;
    }

    while(curr != NULL)
    {
        if(curr->value == value)
        {
            result = 1;
            break;
        }

        parent = curr;
        if(value < curr->value)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return result;
}

int deleteNode(Tree *tree, int value)
{

}

int destroyTree(Tree *tree)
{
    if(tree == NULL)
    {
        return 1;
    }

    destroyNodes(tree->root);
    free(tree);
    return 0;
}

static void destroyNodes(Node *root)
{
    if(root == NULL)
    {
        return;
    }

    destroyNodes(root->left);
    destroyNodes(root->right);

    free(root);
}

int walk(Tree *tree, walkFunc func, int order)
{
    if(tree == NULL)
    {
        return 1;
    }

    switch(order)
    {
        case 1:
            inOrder(tree->root, func);
            break;

        case 2:
            postOrder(tree->root, func);
            break;

        case 3:
            preOrder(tree->root, func);
            break;

        default:
            break;
    }
    return 0;
}

static void inOrder(Node *root, walkFunc func)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        inOrder(root->left, func);
        func(root->value);
        inOrder(root->right, func);
    }
}

static void postOrder(Node *root, walkFunc func)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        postOrder(root->left, func);
        postOrder(root->right, func);
        func(root->value);
    }
}

static void preOrder(Node *root, walkFunc func)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        func(root->value);
        postOrder(root->left, func);
        postOrder(root->right, func);
    }
}