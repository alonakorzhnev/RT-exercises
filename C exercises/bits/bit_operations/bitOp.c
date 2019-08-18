#include <stdio.h>
#include "bitOp.h"

void char2Bin(char c)
{
	int i;
	
    for (i = 7; i >= 0; --i)
    {
		printf( "%d", ( c >> i ) & 1 ? 1 : 0 );
    }
	printf("\n");
}

void int2Bin(int num)
{
	int i = 0, result;
	
	for (i = sizeof(int)*8 - 1; i >= 0; --i)
	{
		result = num >> i;
		if(result & 1)
		{
			printf("1");
		}		  
		else
		{
			printf("0");
		}
	}
}


unsigned char bitInvers(unsigned char n)
{
	return n ^ 255;
}


unsigned char bitRotate(unsigned char n, int steps)
{
	return (n >> steps) | (n << (8 - steps)); 
}

unsigned char setBitsFirst(unsigned char x, int p, int n, unsigned char y)
{
	unsigned char a, b;
	
	a = ~(~0 << n) & y;
	
	b = (~0 << p | ~(~0 << (p - n + 1))) & x; 
	
	return b | (a << (p - n));
}

unsigned int setBitsSecond(unsigned int w, int i, int j, int value)
{
	unsigned int mask;
	
	if(i < 0 || i > 31 || j < 0 || j > 31 || i > j)
	{
		return 0;
	}
	
	mask = (~0 << (32 - j)) & (~(unsigned)0 >> (i - 1));

	if(value == 1)
	{
		return w | mask;
	}
	else if(value == 0)
	{
		return w & ~mask;
	}
}





