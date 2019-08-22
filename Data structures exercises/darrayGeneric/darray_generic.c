#include "darray_generic.h"
#include <stdlib.h>
#include <stdio.h>

struct darray
{
    void **arr;
    size_t index;
    size_t capacity;
    size_t initial_capacity;
};

AdtStatus darrayCreate(darray **dArr, size_t initial_capacity)
{
    *dArr = (darray*)malloc(sizeof(darray));

    if(*dArr == NULL)
    {
        return AllocationError;
    }

    (*dArr)->arr = (void**)malloc(initial_capacity*sizeof(void*));

    if((*dArr)->arr == NULL)
    {
        free(*dArr);
        return AllocationError;
    }

    (*dArr)->index = 0;
    (*dArr)->capacity = initial_capacity;
    (*dArr)->initial_capacity = initial_capacity;

    return OK;
}

AdtStatus darrayDestroy(darray *dArr, elementDestroy destroyFunc, void *context)
{
    int i, size = dArr->index;

    if(dArr == NULL)
    {
        return AllocationError;
    }

    if(dArr->arr == NULL)
    {
        return AllocationError;
    }

    for(i = 0; i < size; ++i)
    {
        destroyFunc(dArr->arr[i], context);
    }

    free(dArr->arr);
    free(dArr);

    return OK;
}

AdtStatus   darrayAdd(darray *dArr,  void  *_item)
{
    void **temp;

    if(dArr == NULL)
    {
        return AllocationError;
    }

    if(dArr->index == dArr->capacity)
    {
        temp = dArr->arr;
        dArr->arr = (void**)realloc(dArr->arr, (dArr->capacity*2)*sizeof(void*));

        if(dArr->arr == NULL)
        {
            dArr->arr = temp;
            return AllocationError;
        }

        (dArr->capacity) *= 2;
    }

    dArr->arr[dArr->index] = _item;
    (dArr->index)++;

    return OK;
}

AdtStatus   darrayDelete(darray *dArr,  void **_item)
{
    void **temp;

    if(dArr == NULL)
    {
        return AllocationError;
    }

    if((dArr->index == dArr->capacity*3/8) && (dArr->capacity != dArr->initial_capacity))
    {
        temp = dArr->arr;
        dArr->arr = (void**)realloc(dArr->arr, (dArr->capacity/2)*sizeof(void*));

        if(dArr->arr == NULL)
        {
            dArr->arr = temp;
            return AllocationError;
        }

        (dArr->capacity) /= 2;
    }

    (dArr->index)--;
    *_item = dArr->arr[dArr->index];    

    return OK;
}

AdtStatus   darrayGet(darray *dArr, size_t _index, void **_item)
{
    if(dArr == NULL)
    {
        return AllocationError;
    }

    *_item = dArr->arr[_index];
    
    return OK;
}

AdtStatus   darraySet(darray *dArr, size_t _index, void  *_item)
{
    if(dArr == NULL)
    {
        return AllocationError;
    }

    dArr->arr[_index] = _item;
    
    return OK;
}

AdtStatus   darrayItemsNum(darray *dArr, int*  _numOfItems)
{
    if(dArr == NULL)
    {
        return AllocationError;
    }

    *_numOfItems = dArr->index;
    
    return OK;
}

static void swap(void** el1, void** el2) 
{ 
    void* temp = *el1;
    *el1 = *el2;
    *el2 = temp;  
} 

static int partition(darray *dArr, int fIndex, int lIndex, elementCompare compareFunc)
{
    void* pivot = dArr->arr[fIndex + (lIndex - fIndex)/2];

    while(1)
    {
        while(compareFunc(dArr->arr[fIndex], pivot) > 0)
        {
            fIndex = fIndex + 1;
        }         

        while(compareFunc(dArr->arr[lIndex], pivot) < 0)
        {
            lIndex = lIndex - 1;
        }
 
        if(fIndex >= lIndex)
        {
            return lIndex;
        }            

        swap(&(dArr->arr[fIndex]), &(dArr->arr[lIndex]));

        fIndex = fIndex + 1;
        lIndex = lIndex - 1;
    }       
}

static void myQuickSort(darray *dArr, int fIndex, int lIndex, elementCompare compareFunc)
{
    int p = 0;

    if(fIndex < lIndex)
    {
        p = partition(dArr, fIndex, lIndex, compareFunc);
        myQuickSort(dArr, fIndex, p, compareFunc);
        myQuickSort(dArr, p + 1, lIndex, compareFunc);
    }
}


AdtStatus darraySort(darray *dArr, elementCompare compareFunc)
{
    myQuickSort(dArr, 0, dArr->index - 1, compareFunc); 

    return OK;
}
  



