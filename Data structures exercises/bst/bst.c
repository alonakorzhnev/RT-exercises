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
static Node* minValueNode(Node* root);
static Node* deleteNodeRecursion(Node *root, int value);
static void destroyTreeRecursion(Node *root);

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

AdtStatus insertNode(Tree *tree, int value)
{
    Node *newNode, *curr, *parent;

    if(tree == NULL)
    {
        return NullPointer;
    }   

    newNode = createNode(value);

    if(newNode == NULL)
    {
        return NullPointer;
    }

    curr = tree->root;
    parent = NULL;

    if(curr == NULL)
    {
        tree->root = newNode;
        return OK;
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

    return OK;
}

AdtStatus searchNode(Tree *tree, int value)
{
    Node *curr, *parent;

    if(tree == NULL)
    {
        return NullPointer;
    }  

    curr = tree->root;
    parent = NULL;

    if(curr == NULL)
    {
        return NullPointer;
    }

    while(curr != NULL)
    {
        if(curr->value == value)
        {
            return IsFound;
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
    return IsNotFound;
}

AdtStatus deleteNode(Tree *tree, int value)
{
    if(tree == NULL)
    {
        return NullPointer;
    }

    tree->root = deleteNodeRecursion(tree->root, value);
    return OK;
}

static Node* deleteNodeRecursion(Node *root, int value)
{
    Node* temp;

    if(root == NULL)
    {
        return root;
    }

    if(value < root->value)
    {
        root->left = deleteNodeRecursion(root->left, value);     
    }
    else if(value > root->value)
    {
        root->right = deleteNodeRecursion(root->right, value);
    }
    else
    {
        if(root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        temp = minValueNode(root->right);
        root->value = temp->value;
        root->right = deleteNodeRecursion(root->right, temp->value);        
    }
    return root;    
}

static Node* minValueNode(Node* root) 
{ 
    Node* curr;

    if(root == NULL)
    {
        return NULL;
    } 

    curr = root;

    while(curr->left != NULL) 
    {
        curr = curr->left;
    }
  
    return curr; 
}

AdtStatus destroyTree(Tree *tree)
{
    if(tree == NULL)
    {
        return NullPointer;
    }

    destroyTreeRecursion(tree->root);
    free(tree);
    return OK;
}

static void destroyTreeRecursion(Node *root)
{
    if(root == NULL)
    {
        return;
    }

    destroyTreeRecursion(root->left);
    destroyTreeRecursion(root->right);

    free(root);
}

AdtStatus walk(Tree *tree, walkFunc func, int order)
{
    if(tree == NULL)
    {
        return NullPointer;
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
    return OK;
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