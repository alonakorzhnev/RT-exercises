/****************************************************************************
    Created by: Yuval Shaul.
    Creation date:      12.8.2019
    Description: Dynamic array, that grows and shrinks automatically.
*****************************************************************************/
#ifndef H_DARRAY
#define H_DARRAY
#include <stdlib.h>

enum AdtStatus {OK, AllocationError}; 

/* forward declaration of the darray type */
typedef struct darray darray;

/* Create a new dynamic array. Return its address in d_arr.
   The initial capacity is the number of items that can be stored
   before a new allocation is needed. */
AdtStatus DarrayCreate(darray **dArr, size_t initial_capacity);
AdtStatus DarrayDestroy(darray *dArr);

/* Add number to the end. */
AdtStatus   DarrayAdd(darray *dArr,  int  _item);
/* Delete number from the end. */
AdtStatus   DarrayDelete(darray *dArr,  int* _item);

AdtStatus   DarrayGet(darray *dArr, size_t _index, int *_item);
AdtStatus   DarraySet(darray *dArr, size_t _index, int  _item);
AdtStatus   DarrayItemsNum(darray *dArr, int*  _numOfItems);

/* in place (ascending) sorting an array of size arraySize */
AdtStatus DarraySort(darray *dArr, size_t arraySize);

#endif