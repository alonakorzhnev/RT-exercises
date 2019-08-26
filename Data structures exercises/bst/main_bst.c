#include "bst.h"
#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


void printValue(int value);
void testCreateTree();
void testInsertNode();
void testDeleteNode();
void testSearchNode();
void testDestroyTree();
void testWalk();

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("bst_test", 0, 0);

    CU_add_test(suite, "createTree", testCreateTree);
    CU_add_test(suite, "insertNode", testInsertNode);
    CU_add_test(suite, "deleteNode", testDeleteNode);
    CU_add_test(suite, "searchNode", testSearchNode);
    CU_add_test(suite, "deleteTree", testDestroyTree);
    CU_add_test(suite, "walk", testWalk);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

void testCreateTree()
{
    Tree *tree = createTree();
    
    /*Tree is not NULL*/
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_FALSE(destroyTree(tree));
}

void testInsertNode()
{
    Tree *tree = createTree();
    Tree *nullTree = NULL;
    
    /*Tree is not NULL*/
    CU_ASSERT_PTR_NOT_NULL(tree);
    /*Insert to null tree*/
    CU_ASSERT_EQUAL(insertNode(nullTree, 5), 1);

    /*Insert nodes to the tree*/
    CU_ASSERT_FALSE(insertNode(tree, 5));
    CU_ASSERT_FALSE(insertNode(tree, 10));
    CU_ASSERT_FALSE(insertNode(tree, 4));
    CU_ASSERT_FALSE(insertNode(tree, 9));
    CU_ASSERT_FALSE(insertNode(tree, 6));

    /*Destroy tree*/
    CU_ASSERT_FALSE(destroyTree(tree));
}

void testDeleteNode()
{
    Tree *tree = createTree();
    Tree *nullTree = NULL;
    
    /*Tree is not NULL*/
    CU_ASSERT_PTR_NOT_NULL(tree);

    /*Insert nodes to the tree*/
    CU_ASSERT_FALSE(insertNode(tree, 5));
    CU_ASSERT_FALSE(insertNode(tree, 7));
    CU_ASSERT_FALSE(insertNode(tree, 6));
    CU_ASSERT_FALSE(insertNode(tree, 8));
    CU_ASSERT_FALSE(insertNode(tree, 3));
    CU_ASSERT_FALSE(insertNode(tree, 2));
    CU_ASSERT_FALSE(insertNode(tree, 4));   

    /*Tree is NULL*/
    CU_ASSERT_EQUAL(deleteNode(nullTree, 5), 1);
    /*Node tobe deleted is leaf*/
    CU_ASSERT_FALSE(deleteNode(tree, 2));
    /*Node tobe deleted has only one child*/
    CU_ASSERT_FALSE(deleteNode(tree, 3));
    /*Node tobe deleted has two children*/
    CU_ASSERT_FALSE(deleteNode(tree, 5));

    /*Destroy tree*/
    CU_ASSERT_FALSE(destroyTree(tree));
}

void testSearchNode()
{
    Tree *tree = createTree();
    Tree *nullTree = NULL;
    
    /*Tree is not NULL*/
    CU_ASSERT_PTR_NOT_NULL(tree);

    /*Insert nodes to the tree*/
    CU_ASSERT_FALSE(insertNode(tree, 5));
    CU_ASSERT_FALSE(insertNode(tree, 7));
    CU_ASSERT_FALSE(insertNode(tree, 6));
    CU_ASSERT_FALSE(insertNode(tree, 8));
    CU_ASSERT_FALSE(insertNode(tree, 3));
    CU_ASSERT_FALSE(insertNode(tree, 2));
    CU_ASSERT_FALSE(insertNode(tree, 4));   

    /*Search in NULL tree*/
    CU_ASSERT_EQUAL(searchNode(nullTree, 5), 1);
    /*Search existing elements*/
    CU_ASSERT_EQUAL(searchNode(tree, 5), 2);
    CU_ASSERT_EQUAL(searchNode(tree, 8), 2);
    CU_ASSERT_EQUAL(searchNode(tree, 3), 2);
    /*Search not existing elements*/
    CU_ASSERT_EQUAL(searchNode(tree, 50), 3);
    CU_ASSERT_EQUAL(searchNode(tree, 80), 3);
    CU_ASSERT_EQUAL(searchNode(tree, 30), 3);

    /*Destroy tree*/
    CU_ASSERT_FALSE(destroyTree(tree));
}

void testDestroyTree()
{
    Tree *tree = createTree();
    Tree *nullTree = NULL;
    
    /*Tree is not NULL*/
    CU_ASSERT_PTR_NOT_NULL(tree);

    /*Destroy NULL tree*/
    CU_ASSERT_EQUAL(destroyTree(nullTree), 1);
    /*Destroy not NULL tree*/
    CU_ASSERT_FALSE(destroyTree(tree));
}

void testWalk()
{
    Tree *tree = createTree();
    Tree *nullTree = NULL;
    walkFunc func = printValue;
    
    /*Tree is not NULL*/
    CU_ASSERT_PTR_NOT_NULL(tree);

    /*Insert nodes to the tree*/
    CU_ASSERT_FALSE(insertNode(tree, 5));
    CU_ASSERT_FALSE(insertNode(tree, 7));
    CU_ASSERT_FALSE(insertNode(tree, 6));
    CU_ASSERT_FALSE(insertNode(tree, 8));
    CU_ASSERT_FALSE(insertNode(tree, 3));
    CU_ASSERT_FALSE(insertNode(tree, 2));
    CU_ASSERT_FALSE(insertNode(tree, 4));   

    /*Walk in NULL tree*/
    CU_ASSERT_EQUAL(walk(nullTree, func, 1), 1);
    /*Walk in not NULL tree inorder*/
    CU_ASSERT_FALSE(walk(tree, func, 1));
    printf("  ");
    /*Walk in not NULL tree postorder*/
    CU_ASSERT_FALSE(walk(tree, func, 2));
    printf("  ");
    /*Walk in not NULL tree preorder*/
    CU_ASSERT_FALSE(walk(tree, func, 3));
    
    /*Destroy tree*/
    CU_ASSERT_FALSE(destroyTree(tree));   
}

void printValue(int value)
{
    printf("%d ", value);
}