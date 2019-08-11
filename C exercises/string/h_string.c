#include "h_string.h"

void Int2Bin(int num, char* result)
{
	int bin_num[32];
	int i = 0, j;

	if(result == NULL)
	{
		return;
	}
	
	while(num > 0)
	{
		bin_num[i] = num%2;
		num /= 2;
		++i;
	}

	for(j = 0; j < i; ++j)
	{
		result[j] = bin_num[i - j - 1] + 48;			
	}
	
	result[j] = '\0';	

	printf("Result: %s\n\n", result);
}

void Bin2Int(char* string)
{
	int num = atoi(string);
	int result = 0, base = 1, last_digit;

	if(string == NULL)
	{
		return;
	}
	
	while(num > 0)
	{
		last_digit = num%10;
		result += last_digit*base;
		num /= 10;
		base *= 2;
	}

	printf("Result: %d\n\n", result);	
}

void squeeze(char* s1,char* s2)
{
	int i, j, k = 0;
	
	if(s1 == NULL || s2 == NULL)
	{
		return;
	}
	
	for(i = 0; s1[i] != '\0'; ++i)
	{
		j = 0;
		while(s1[i] != s2[j] && s2[j] != '\0')
		{
			++j;
		}
		
		if(s2[j] == '\0')
		{
			s1[k] =s1[i];
			++k;
		}
	}
	
	s1[k] = '\0';
	
	printf("Result: %s\n\n", s1);
}

int location(char* s1, char* s2)
{
	int i = 0, j, k;
	
	if(s1 == NULL || s2 == NULL)
	{
		return;
	}
	
	while(s1[i] != '\0')
	{
		j = 0;
		k = i;
		
		while(s1[k] != '\0' && s2[j] != '\0' && s1[k] == s2[j])
		{
			++k;
			++j;
		}
		
		if(s2[j] == '\0')
		{
			return i;
		}
		
		++i;
	}
	return -1;
}
