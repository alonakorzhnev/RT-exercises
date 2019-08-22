#include "darray_generic.h"
#include <stdlib.h>
#include <stdio.h>

struct darray
{
    int **arr;
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
        dArr->arr = (int**)realloc(dArr->arr, (dArr->capacity*2)*sizeof(void*));

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

static void swap(void* el1, void* el2, size_t size) 
{ 
    char buffer[size];

    memcpy(buffer, el1, size); 
    memcpy(el1, el2, size); 
    memcpy(el2, buffer, size); 
} 

static void myQsort(void* v, size_t size, int left, int right, 
                    elementCompare compareFunc) 
{ 
    void *vt, *v3; 
    int i, last, mid = (left + right)/2; 

    if (left >= right)
    {
        return;
    }
 
    void* vl = (char*)(v + (left * size)); 
    void* vr = (char*)(v + (mid * size));

    swap(vl, vr, size); 
    last = left; 

    for (i = left + 1; i <= right; i++) 
    { 
        vt = (char*)(v + (i * size)); 

        if (compareFunc(vl, vt) > 0) 
        { 
            ++last; 
            v3 = (char*)(v + (last*size)); 

            swap(vt, v3, size); 
        } 
    } 

    v3 = (char*)(v + (last * size)); 
    swap(vl, v3, size); 

    myQsort(v, size, left, last - 1, compareFunc); 
    myQsort(v, size, last + 1, right, compareFunc); 
} 

AdtStatus darraySort(darray *dArr, elementCompare compareFunc, size_t size)
{
    
    return OK;
}
  



