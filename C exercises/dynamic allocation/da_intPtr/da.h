#ifndef DA_H
#define DA_H

typedef int* intPtr;

typedef struct{
    intPtr* arr;
    int capacity;
    int index;
}da_str;

da_str* createArray(int cap);

int insert(da_str* da, intPtr num);

void print(da_str* da);

void destroy(da_str* da);

#endif
