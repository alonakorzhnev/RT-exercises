#ifndef BST_H
#define BST_H

typedef struct Tree Tree;

typedef void (*walkFunc)(int value);

Tree* createTree();

int insertNode(Tree *tree, int value);

int searchNode(Tree *tree, int value);

int deleteNode(Tree *tree, int value);

int destroyTree(Tree *tree);

int walk(Tree *tree, walkFunc func, int order);

#endif
