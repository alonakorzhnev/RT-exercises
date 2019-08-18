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


unsigned char bitInvers(unsigned char n)
{
	return n ^ 255;
}


unsigned char bitRotate(unsigned char n, int steps)
{
	return (n >> steps) | (n << (8 - steps)); 
}

unsigned char setBits1(unsigned char x, int p, int n, unsigned char y)
{
	unsigned char mask;
	
	y <<= p - 1;
	y >>= 8 - n;
	y <<= p - 2 -1;
	
	return x | y;
}