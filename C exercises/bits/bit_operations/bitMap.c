#include <stdio.h>
#include <stdlib.h>
#include "bitMap.h"


static void int2Bin(int num)
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

int callFunc(bitFunc func, BitMap* bm, int n)
{
	return func(bm, n);
}

BitMap* createBM(int nf)
{
	BitMap* bm;
	int countInt = (nf - 1)/(sizeof(int)*8) + 1;
	
	bm = (BitMap*)malloc(sizeof(BitMap));
	
	if(bm == NULL)
	{
		return NULL;
	}
	
	bm->m_arr = (int*)calloc(countInt, sizeof(int));
	
	if(bm->m_arr == NULL)
	{
		free(bm);
		return NULL;
	}
	
	bm->m_nf = nf;
	
	printBM(bm);
	
	return bm;
}

void destroyBM(BitMap* bm)
{
	if(bm == NULL);
	{
		return;
	}
	
	free(bm->m_arr);
	
	free(bm);
}

int bitOn(BitMap* bm, int n)
{
	unsigned int intIndex, bitIndex, switcher = 1;
	
	if(bm == NULL)
	{
		return -1;
	}
	
	if(n > bm->m_nf)
	{
		return -1;
	}
	
	intIndex = (n - 1)/(sizeof(int)*8);
	bitIndex = n%(sizeof(int)*8);	
	
	switcher <<= 32 - bitIndex;		
	bm->m_arr[intIndex] = bm->m_arr[intIndex] | switcher;
	
	return 0;
}

int bitOff(BitMap* bm, int n)
{
	unsigned int intIndex, bitIndex, switcher = 1;
	
	if(bm == NULL)
	{
		return -1;
	}
	
	if(n > bm->m_nf)
	{
		return -1;
	}
	
	intIndex = (n - 1)/(sizeof(int)*8);
	bitIndex = n%(sizeof(int)*8);	
	
	switcher <<= 32 - bitIndex;		
	switcher =~ switcher;
	bm->m_arr[intIndex] = bm->m_arr[intIndex] & switcher;
	
	return 0;
}

int bitStatus(BitMap* bm, int n)
{
	unsigned int intIndex, bitIndex, switcher = 1;
	int result;
	
	if(bm == NULL)
	{
		return -1;
	}
	
	if(n > bm->m_nf)
	{
		return -1;
	}
	
	intIndex = (n - 1)/(sizeof(int)*8);
	bitIndex = n%(sizeof(int)*8);
	
	switcher <<= 32 - bitIndex;		
	
	result = bm->m_arr[intIndex] & switcher;
	
	return result ? 1 : 0;
}

int printBM(BitMap* bm)
{
	int countInt = (bm->m_nf - 1)/(sizeof(int)*8) + 1;
	int i;
	
	if(bm == NULL)
	{
		return -1;
	}
	
	for(i = 0; i < countInt; ++i)
	{
		int2Bin(bm->m_arr[i]);
	}
	
	printf("\n\n");
	
	return 0;
}




