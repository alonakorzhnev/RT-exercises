#include "bst.h"
#include <stdio.h>

void printValue(int value);


int main()
{
    Tree *tree;
    int cont = 1, value, result;
    unsigned int option;
    walkFunc func = printValue;

    tree = createTree();
    if(tree == NULL)
    {
        return 0;
    }

    while(cont)
    {
        printf("\nChoose option:\n");
		printf("1: Insert node\n");
		printf("2: Delete node\n");
		printf("3: Search node\n");
        printf("4: Walk\n");
		printf("Any another number - stop\n");
		
		scanf("%x", &option);
		switch(option)
		{
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                result = insertNode(tree, value);
                break;

            case 2:

                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                result = searchNode(tree, value);

                if(result)
                {
                    printf("The value is found\n");
                }
                else
                {
                    printf("The value is not found\n");
                }

                break;

            case 4:
                printf("Enter type of order to walk(1-inorder, 2-postorder, 3-preorder): ");
                scanf("%d", &value);
                result = walk(tree, func, value);
                break;

            default:
                cont = 0;
                break;
        }
    }

    result = destroyTree(tree);
    return 0;
}

void printValue(int value)
{
    printf("%d ", value);
}