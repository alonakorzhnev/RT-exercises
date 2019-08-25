#include "bst.h"
#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


void printValue(int value);
void testCreateTree();
void testInsertNode();

int main()
{
    /*Tree *tree;
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
                printf("Enter value to delete: ");
                scanf("%d", &value);
                result = deleteNode(tree, value);
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

    result = destroyTree(tree);*/
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("bst_test", 0, 0);

    CU_add_test(suite, "createTree", testCreateTree);
    CU_add_test(suite, "insertNode", testInsertNode);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

void testCreateTree()
{
    Tree *tree = createTree();
    
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_FALSE(destroyTree(tree));
}

void testInsertNode()
{
    Tree *tree = createTree();
    Tree *nullTree = NULL;
    
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_EQUAL(insertNode(nullTree, 5), 1);
    CU_ASSERT_FALSE(insertNode(tree, 5));
    CU_ASSERT_FALSE(insertNode(tree, 10));
    CU_ASSERT_FALSE(insertNode(tree, 4));
    CU_ASSERT_FALSE(insertNode(tree, 9));
    CU_ASSERT_FALSE(insertNode(tree, 6));
    CU_ASSERT_FALSE(destroyTree(tree));
}

void printValue(int value)
{
    printf("%d ", value);
}