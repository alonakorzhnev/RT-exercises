#include "hashTable.h"
#include <stdio.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void printFunc(void *key, void *value, void *context);
unsigned long hashFunc(void *key);
int compareFunc(void *keyA, void *keyB);
void destroyFunc(void *key, void *value);

void testCreate();
void testDestroy();
void tetsInsert();
void testRemove();
void testFind();
void testForEach();


int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("hash_test", 0, 0);

    CU_add_test(suite, "testCreate", testCreate);
    CU_add_test(suite, "testDestroy", testDestroy);
    CU_add_test(suite, "tetsInsert", tetsInsert);
    CU_add_test(suite, "testRemove", testRemove);
    CU_add_test(suite, "testFind", testFind);    
    CU_add_test(suite, "testForEach", testForEach);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

void printFunc(void *key, void *value, void *context)
{
    int *intPtr = (int*)context;
    ++(*intPtr);

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
    CU_ASSERT_EQUAL(hashTableDestroy(nullHashT, destroyF), NullPointer);
    /*Destroy hash with elements*/
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 100, hashF, compF));
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1234567", "Alona"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "5754839", "Rami"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "2874772", "Oren"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1039483", "Mariana"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1048373", "Aviv"), OK);
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
}

void tetsInsert()
{
    HashTable *hashT, *nullHashT = NULL;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    elementDestroy destroyF = destroyFunc;
    void *voidPtr;

    /*Insert to NULL hash*/
    CU_ASSERT_EQUAL(hashTableInsert(nullHashT, "1234567", "Alona"), NullPointer);
    /*Multiple insert*/
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 5, hashF, compF));
    CU_ASSERT_PTR_NOT_NULL(hashT);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1234567", "Alona"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "5754839", "Rami"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "2874772", "Oren"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1039483", "Mariana"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1048373", "Aviv"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "7597935", "Alex"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "9547484", "Maxim"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "7336566", "Margo"), OK);
    /*Check insert by found value*/
    CU_ASSERT_EQUAL(hashTableFind(hashT, "9547484", &voidPtr), IsFound);
    CU_ASSERT_STRING_EQUAL((char*)voidPtr, "Maxim");
    /*Insert existed element*/
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1039483", "Mariana"), IsFound);
    /*Insert NULL key*/
    CU_ASSERT_EQUAL(hashTableInsert(hashT, NULL, "Mariana"), NullPointer);
    /*Insert NULL value*/
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "5462324", NULL), NullPointer);
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
}

void testRemove()
{
    HashTable *hashT, *nullHashT = NULL;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    elementDestroy destroyF = destroyFunc;
    void *voidPtr;

    /*Remove from NULL hash*/
    CU_ASSERT_EQUAL(hashTableRemove(nullHashT, "1234567", &voidPtr, destroyF), NullPointer);
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 5, hashF, compF));
    CU_ASSERT_PTR_NOT_NULL(hashT);
    /*Multiple insert*/
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1234567", "Alona"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "5754839", "Rami"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "2874772", "Oren"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1039483", "Mariana"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1048373", "Aviv"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "7597935", "Alex"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "9547484", "Maxim"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "7336566", "Margo"), OK);
    /*Remove NULL key*/
    CU_ASSERT_EQUAL(hashTableRemove(hashT, NULL, &voidPtr, destroyF), NullPointer);
    /*Remove not existed element*/
    CU_ASSERT_EQUAL(hashTableRemove(hashT, "9643746", &voidPtr, destroyF), IsNotFound);
    /*Remove existed element*/
    CU_ASSERT_EQUAL(hashTableRemove(hashT, "1234567", &voidPtr, destroyF), OK);
    CU_ASSERT_STRING_EQUAL((char*)voidPtr, "Alona");
    /*Check remove by found value*/
    CU_ASSERT_EQUAL(hashTableFind(hashT, "1234567", &voidPtr), IsNotFound);
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
}

void testFind()
{
    HashTable *hashT, *nullHashT = NULL;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    elementDestroy destroyF = destroyFunc;
    void *voidPtr;

    /*Find in NULL hash*/
    CU_ASSERT_EQUAL(hashTableFind(nullHashT, "1234567", &voidPtr), NullPointer);
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 5, hashF, compF));
    CU_ASSERT_PTR_NOT_NULL(hashT);
    /*Multiple insert*/
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1234567", "Alona"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "5754839", "Rami"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "2874772", "Oren"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1039483", "Mariana"), OK);
    /*Find existed value*/
    CU_ASSERT_EQUAL(hashTableFind(hashT, "1234567", &voidPtr), IsFound);
    CU_ASSERT_STRING_EQUAL((char*)voidPtr, "Alona");
    /*Find not existed value*/
    CU_ASSERT_EQUAL(hashTableFind(hashT, "8848744", &voidPtr), IsNotFound);
    /*Find NULL key*/
    CU_ASSERT_EQUAL(hashTableFind(hashT, NULL, &voidPtr), NullPointer);
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
}

void testForEach()
{
    int context = 0;
    int *contextPtr = &context;
    void *voidPtr;
    HashTable *hashT, *nullHashT = NULL;
    hashFunction hashF = hashFunc;
    elementCompare compF = compareFunc;
    elementDestroy destroyF = destroyFunc;
    forEachFunction forEachF = printFunc;

    /*ForEach in NULL hash*/
    CU_ASSERT_EQUAL(hashTableForEach(nullHashT, forEachF, contextPtr), NullPointer);
    CU_ASSERT_FALSE(hashTableCreate(&hashT, 5, hashF, compF));
    CU_ASSERT_PTR_NOT_NULL(hashT);
    /*Multiple insert*/
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1234567", "Alona"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "5754839", "Rami"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "2874772", "Oren"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1039483", "Mariana"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "1048373", "Aviv"), OK);
    CU_ASSERT_EQUAL(hashTableInsert(hashT, "7597935", "Alex"), OK);
    CU_ASSERT_EQUAL(hashTableRemove(hashT, "1234567", &voidPtr, destroyF), OK);
    CU_ASSERT_EQUAL(hashTableRemove(hashT, "5754839", &voidPtr, destroyF), OK);
    /*ForEach in not NULL hash*/
    CU_ASSERT_EQUAL(hashTableForEach(hashT, forEachF, contextPtr), OK);
    CU_ASSERT_EQUAL(context, 4);
    CU_ASSERT_FALSE(hashTableDestroy(hashT, destroyF));
}