#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw_files.h"

int last(char* fileName, int n)
{
	FILE* fp;
	char str[512];
	int* array;
	char* c;
	int offset = 0, i = 0;
	long int pos;
	
	if((fp = fopen(fileName, "r")) == NULL)
	{
		printf("Cannot open file\n");
		return -1;
	}
	
	array = (int*)malloc(n*sizeof(int));
	
	if(array == NULL)
	{
		return -1;
	}
	
	array[i] = offset;
	
	do{
	
		c = fgets(str, 512, fp);
		offset += ftell(fp);
		i = i%n;
		array[i] = offset;
		i++;	
		
	}while(c != NULL);
	
	pos = ftell(fp);
	
	
	if(fclose(fp) != 0)
	{
		return -1;
	}
	
	free(array);
}

