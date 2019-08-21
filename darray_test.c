#include "darray_generic.h"
#include <stdio.h>
#include <math.h>

typedef struct 
{
   int x;
   int y;
}Point;

Point* createPoint(int x, int y);
void elDestroy(void *element, void* fileName);
void addElement(darray *dArr);
void deleteElement(darray *dArr, char* fileName);
void setElement(darray *dArr, char* fileName);
void printElements(darray *dArr);
int elCompare(void *_elemA, void *_elemB);
void sortElements(darray* dArr, elementCompare compareFunc);


int main()
{
    darray *myDarr;
    int capacity, numOfItems;
    int status, i, cont = 1;
    unsigned int option;
    elementDestroy fDestroy = elDestroy;
    elementCompare fCompare = elCompare;
    Point *point;
    char fileName[32];

    printf("Enter initial capacity of array: ");
    scanf("%d", &capacity);

    status = darrayCreate(&myDarr, capacity);

    if(status)
    {
        printf("Error in darrayCreate!");
        return 0;
    }

    printf("Enter name of file to save elements: ");
    scanf("%s", fileName);

    while(cont)
	{
		printf("Choose option:\n");
		printf("1: Add item\n");
		printf("2: Delete item\n");
		printf("3: Set item\n");
        printf("4: Sort array\n");
        printf("5: Print array\n");
		printf("Any another number - stop\n");
		
		scanf("%x", &option);
		switch(option)
		{
			case 1:	
                addElement(myDarr);				
				break;
			
			case 2:               
				deleteElement(myDarr, fileName);	
				break;				
			
			case 3:
				setElement(myDarr, fileName);
				break;

            case 4:                
                sortElements(myDarr, fCompare);
                break;

            case 5:
                printElements(myDarr);
                break;
				
			default:
				cont = 0;
				break;
		}
	}    

    status = darrayDestroy(myDarr, fDestroy, fileName);

    if(status)
    {
        printf("Error in darrayDestroy!");
    }

    return 0;
}

Point* createPoint(int x, int y)
{
    Point* pointPtr;

    pointPtr = (Point*)malloc(sizeof(Point));

    if(pointPtr == NULL)
    {
        return NULL;
    }

    pointPtr->x = x;
    pointPtr->y = y;

    return pointPtr;
}

void elDestroy(void* element, void* fileName)
{
    FILE* fp;

    if((Point*)element == NULL)
    {
        return;
    }

    if((fp = fopen((char*)fileName, "a")) == NULL)
    {
        return;
    }

    fprintf(fp, "x = %d, y = %d\n", ((Point*)element)->x, ((Point*)element)->y);

    fclose(fp);
    free((Point*)element);
}

void addElement(darray *dArr)
{
    int x, y, status;
    Point *point;

    printf("Enter x and y value of struct to add: ");
    scanf("%d%d", &x, &y);

    point = createPoint(x, y);

    if(point == NULL)
    {
        printf("Error in createPoint\n");
        return;
    }
				
    status = darrayAdd(dArr,  point);

    if(status)
    {
        printf("Error in darrayAdd\n");
        return;
    }
}

void deleteElement(darray *dArr, char* fileName)
{
    Point *pointPtr;
    int status;
    void* voidPtr;

    if(dArr == NULL)
    {
        return;
    }
    
    status = darrayDelete(dArr,  &voidPtr);
    pointPtr = (void*)voidPtr; 
    elDestroy(pointPtr, fileName);    
}

void setElement(darray *dArr, char* fileName)
{
    Point *pointPtr;
    void* voidPtr;
    int index, status;
    int x, y;

    printf("Enter index of element to set: ");
    scanf("%d", &index);

    status = darrayGet(dArr, index, &voidPtr);

    if(voidPtr == NULL)
    {
        return;
    }

    pointPtr = (void*)voidPtr;
    elDestroy(pointPtr, fileName);

    printf("Enter x and y value of struct to set: ");
    scanf("%d%d", &x, &y);

    pointPtr = createPoint(x, y);
				
    status = darraySet(dArr, index, pointPtr);    
}

void printElements(darray *dArr)
{
    int numOfItems = 0, i, status;
    Point *pointPtr;
    void* voidPtr;

    status = darrayItemsNum(dArr, &numOfItems);

    if(status)
    {
        printf("Error in darrayItemsNum!");
        return;
    }

    for(i = 0; i < numOfItems; ++i)
    {
        status = darrayGet(dArr, i, &voidPtr); 
        pointPtr = (void*)voidPtr; 

        if(status)
        {
            printf("Error in darrayGet!");
            break;
        }

        printf("x = %d y = %d\n" , pointPtr->x, pointPtr->y);                  
    }

    printf("\n"); 
}

int elCompare(void *_elemA, void *_elemB)
{
    int xA, yA, xB, yB;

    xA = ((Point*)_elemA)->x;
    yA = ((Point*)_elemA)->y;
    xB = ((Point*)_elemB)->x;
    yB = ((Point*)_elemB)->y;

    if(sqrt(pow(xA, 2) + pow(yA, 2)) > sqrt(pow(xB, 2) + pow(yB, 2)))
    {
        return 1;
    }
    else if(sqrt(pow(xA, 2) + pow(yA, 2)) < sqrt(pow(xB, 2) + pow(yB, 2)))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void sortElements(darray* dArr, elementCompare compareFunc)
{
    int status;

    if(dArr == NULL)
    {
        return;
    }

    status = darraySort(dArr, compareFunc);

    if(status)
    {
        printf("Error in darraySort!");
    }
}
