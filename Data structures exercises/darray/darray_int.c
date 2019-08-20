#include "darray_int.h"
#include <stdlib.h>
#include <stdio.h>

struct darray
{
    int* arr;
    size_t index;
    size_t capacity;
};


AdtStatus DarrayCreate(darray **dArr, size_t initial_capacity)
{
    *dArr = (darray*)malloc(sizeof(darray));

    if(dArr == NULL)
    {
        return AllocationError;
    }

    dArr->arr = (int*)malloc(initial_capacity*sizeof(int));

    if(dArr->arr == NULL)
    {
        free(dArr);
        return AllocationError;
    }

}


AdtStatus DarrayDestroy(darray *dArr);


AdtStatus   DarrayAdd(darray *dArr,  int  _item);
AdtStatus   DarrayDelete(darray *dArr,  int* _item);

AdtStatus   DarrayGet(darray *dArr, size_t _index, int *_item);
AdtStatus   DarraySet(darray *dArr, size_t _index, int  _item);
AdtStatus   DarrayItemsNum(darray *dArr, int*  _numOfItems);

AdtStatus DarraySort(darray *dArr, size_t arraySize);