#include "darray_int.h"
#include <stdio.h>

int main()
{
    darray *myDarr;
    int capacity, item, numOfItems;
    int status, i, cont = 1;
    unsigned int option;


    printf("Enter initial capacity of array: ");
    scanf("%d", &capacity);

    status = darrayCreate(&myDarr, capacity);

    if(status)
    {
        printf("Error in darrayCreate!");
        return 0;
    }

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
                printf("Enter item value to add: ");
                scanf("%d", &item);
				
                status = darrayAdd(myDarr,  item);

                if(status)
                {
                    printf("Error in darrayAdd!");
                }
				
				break;
			
			case 2:               
				
                status = darrayDelete(myDarr,  &item);

                if(status)
                {
                    printf("Error in darrayDelete!");
                }

                printf("Deleted item value: %d\n", item);
				
				break;				
			
			case 3:
				printf("Enter item index and value to set: ");
                scanf("%d%d", &i, &item);
				
                status = darraySet(myDarr, i, item);

                if(status)
                {
                    printf("Error in darraySet!");
                }

				break;

            case 4:

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

                break;
				
			default:
				cont = 0;
				break;
		}
	}    

    status = darrayDestroy(myDarr);

    if(status)
    {
        printf("Error in darrayDestroy!");
    }

    return 0;
}