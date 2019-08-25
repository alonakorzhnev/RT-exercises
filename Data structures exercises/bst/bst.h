#ifndef BST_H
#define BST_H

typedef struct Tree Tree;
typedef void (*walkFunc)(int value);
typedef enum {OK, NullPointer, IsFound, IsNotFound} AdtStatus;

Tree* createTree();

AdtStatus insertNode(Tree *tree, int value);

AdtStatus searchNode(Tree *tree, int value);

AdtStatus deleteNode(Tree *tree, int value);

AdtStatus destroyTree(Tree *tree);

AdtStatus walk(Tree *tree, walkFunc func, int order);

#endif
