#include <stdio.h>
#include <string.h>
#include "bit_pack.h"

static void char2Bin(char c)
{
	int i;
	
    for (i = 7; i >= 0; --i)
    {
		printf( "%d", ( c >> i ) & 1 ? 1 : 0 );
    }
}

int withoutBitField(char* string)
{	
	int size = strlen(string), i = 0, index = 0;
	char left, right, result;
	
	for(i = 0; i < size; i += 2)
	{			
		left = string[i] - 'a';
		
		if(string[i + 1] == '\0')
		{
			right = 0;
		}
		else
		{
			right = string[i + 1] - 'a';
		}
				
		left <<= 4;
		result = left | right;	
		
		string[index] = result;	
		++index;
	}	
	string[index] = '\0';
		
	return size;
}

int withBitField(char* string)
{
	int size = strlen(string), i = 0, index = 0;
	char left, right;
	union un u;	
	
	for(i = 0; i < size; i += 2)
	{			
		left = string[i] - 'a';
		
		if(string[i + 1] == '\0')
		{
			right = 0;
		}
		else
		{
			right = string[i + 1] - 'a';
		}
		
		u.charPack.m_left = left;		
		u.charPack.m_right = right;
				
		string[index] = u.c;
		++index;
	}	
	string[index] = '\0';
	
	return size;
}

void printBits(char* string, int size)
{
	int i;
	
	for(i = 0; i < size; ++i)
	{
		char2Bin(string[i]);
		putchar(' ');
	}
	putchar('\n');
}