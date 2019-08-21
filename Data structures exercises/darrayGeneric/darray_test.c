#include "darray_generic.h"
#include <stdio.h>

typedef struct 
{
   int x;
   int y;
}Point;

Point* createPoint(int x, int y);
AdtStatus elDestroy(Point *element, char* fileName);
AdtStatus addElement(darray *dArr);
AdtStatus deleteElement(darray *dArr, char* fileName);

int main()
{
    darray *myDarr;
    int capacity, numOfItems;
    int status, i, cont = 1;
    unsigned int option;
    elementDestroy elDestroy;
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
                status = addElement(myDarr);				
				break;
			
			case 2:               
				status = deleteElement(myDarr, fileName);	
				break;				
			
			case 3:
				

				break;

            /*case 4:

                status = darraySort(myDarr);

                if(status)
                {
                    printf("Error in darraySort!");
                }

                break;

            case 5:
                numOfItems = 0;
                status = darrayItemsNum(myDarr, &numOfItems);

                if(status)
                {
                    printf("Error in darrayItemsNum!");
                    cont = 0;
                }

                for(i = 0; i < numOfItems; ++i)
                {
                    status = darrayGet(myDarr, i, &item);  

                    if(status)
                    {
                        printf("Error in darrayGet!");
                    }

                    printf("%d " , item);                  
                }

                printf("\n");   

                break;*/
				
			default:
				cont = 0;
				break;
		}
	}    

    status = darrayDestroy(myDarr, *elDestroy, fileName);

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

AdtStatus elDestroy(Point* element, char* fileName)
{
    FILE* fp;

    if(element == NULL)
    {
        return NullPointer;
    }

    if((fp = fopen(fileName, "a")) == NULL)
    {
        return NullPointer;
    }

    fprintf(fp, "x = %d, y = %d\n", element->x, element->y);

    fclose(fp);
    free(element);
}

AdtStatus addElement(darray *dArr)
{
    int x, y, status;
    Point *point;

    printf("Enter x and y value of struct to add: ");
    scanf("%d%d", &x, &y);

    point = createPoint(x, y);

    if(point == NULL)
    {
        return NullPointer;
    }
				
    status = darrayAdd(dArr,  point);

    if(status)
    {
        return NullPointer;
    }

    return OK;
}

AdtStatus deleteElement(darray *dArr, char* fileName)
{
    Point *pointPtr;
    int status;
    void* voidPtr;
    
    status = darrayDelete(dArr,  &voidPtr);
    pointPtr = (void*)voidPtr; 
    status = elDestroy(pointPtr, fileName);

    return OK;    
}

/*AdtStatus setElement(darray *dArr, char* fileName)
{
    Point *point;
    int index, status;

    printf("Enter index of element to set: ");
    scanf("%d", &index);

    status = darrayGet(dArr, index, *point);

    if(point == NULL)
    {
        return NullPointer;
    }

    status = elDestroy(point, fileName);

    point = createPoint(x, y);
				
    status = darraySet(myDarr, index, point);    

    return OK;
}*/

