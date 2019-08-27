#include "hashTable.h"
#include <stdio.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void printFunc(void *key, void *value);
unsigned long hashFunc(void *key);
int compareFunc(void *keyA, void *keyB);
void destroyFunc(void *key, void *value);

void testCreate();
void testDestroy();
void tetsInsert();
/*void testRemove();
void testFind();
void testForEach();*/


int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("hash_test", 0, 0);

    CU_add_test(suite, "testCreate", testCreate);
    CU_add_test(suite, "testDestroy", testDestroy);
    CU_add_test(suite, "tetsInsert", tetsInsert);
    /*CU_add_test(suite, "testRemove", testRemove);
    CU_add_test(suite, "testFind", testFind);    
    CU_add_test(suite, "testForEach", testForEach);*/

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    /*AdtStatus status;
    int size = 100;
    HashTable *hashT;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    forEachFunction forEachPrint = printFunc;
    elementDestroy destroyF = destroyFunc;

    void *foundPtr;
    char *foundStr;
    char *key1 = "12345678";
    char *value1 = "12345678";

    char *key2 = "12345678";
    char *value2 = "1234909";
    char *key3 = "67555544478";


    status = hashTableCreate(&hashT, size, hashF, compF);

    status = hashTableInsert(hashT, key1, value1);
    status = hashTableInsert(hashT, key2, value2);
    status = hashTableInsert(hashT, "4567988", "9776756");


    status = hashTableFind(hashT, key1, &foundPtr);
    foundStr = (char*)foundPtr;
    printf("%d\n", status);
    status = hashTableFind(hashT, key2, &foundPtr);
    foundStr = (char*)foundPtr;
    printf("%d\n", status);
    status = hashTableFind(hashT, key3, &foundPtr);
    foundStr = (char*)foundPtr;
    printf("%d\n", status);
    
    status = hashTableForEach(hashT, forEachPrint);

    status = hashTableRemove(hashT, key1, &foundPtr, destroyFunc);
    foundStr = (char*)foundPtr;
    printf("%s\n", foundStr);

    status = hashTableForEach(hashT, forEachPrint);

    printf("\n");
    status = hashTableDestroy(hashT, destroyF);*/

    return 0;
}

void printFunc(void *key, void *value)
{
    printf("key = %s, value = %s -> ", (char*)key, (char*)value);
}

unsigned long hashFunc(void *key)
{
    unsigned long hash = 5381;
    int c;
    unsigned char *str = (unsigned char*)key;

    while ((c = *str++) != 0)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int compareFunc(void *keyA, void *keyB)
{
    if(keyA == NULL || keyB == NULL)
    {
        return -1;
    }

    if(strcmp((char*)keyA, (char*)keyB) == 0)
    {
        return 0;
    }
 
    return -1;
}

void destroyFunc(void *key, void *value)
{
    printf("Destroy: key = %s, value = %s\n", (char*)key, (char*)value);
}

void testCreate()
{
    HashTable *hashT;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    elementDestroy destroyF = destroyFunc;

    CU_ASSERT_EQUAL(hashTableCreate(&hashT, 0, hashF, compF), 1);
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 100, hashF, compF));
    CU_ASSERT_PTR_NOT_NULL(hashT);
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
}

void testDestroy()
{
    HashTable *hashT, *nullHashT = NULL;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    elementDestroy destroyF = destroyFunc;

    /*Destroy hash without elements*/
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 100, hashF, compF));
    CU_ASSERT_PTR_NOT_NULL(hashT);
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
    /*Destroy NULL*/
    CU_ASSERT_EQUAL(hashTableDestroy(nullHashT, destroyF), 3);
    /*Destroy hash with elements*/
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 100, hashF, compF));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "1234567", "Alona"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "5754839", "Rami"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "2874772", "Oren"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "1039483", "Mariana"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "1048373", "Aviv"));
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
}

void tetsInsert()
{
    HashTable *hashT, *nullHashT = NULL;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    elementDestroy destroyF = destroyFunc;

    /*Multiple insert*/
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 5, hashF, compF));
    CU_ASSERT_PTR_NOT_NULL(hashT);
    CU_ASSERT_FALSE(hashTableInsert(hashT, "1234567", "Alona"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "5754839", "Rami"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "2874772", "Oren"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "1039483", "Mariana"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "1048373", "Aviv"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "7597935", "Alex"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "9547484", "Maxim"));
    CU_ASSERT_FALSE(hashTableInsert(hashT, "7336566", "Margo"));
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
    /*Insert to NULL hash*/
    CU_ASSERT_EQUAL(hashTableInsert(nullHashT, "1234567", "Alona"), NullPointer);


}