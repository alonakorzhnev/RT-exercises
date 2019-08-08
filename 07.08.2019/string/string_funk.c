#include <stdio.h>

int my_strcmp(char* first, char* second);
void my_strcpy(char* dest, char* source);
void my_strcat(char* dest, char* source);

int my_strcmp(char* first, char* second)
{
	int flag = 0, i = 0;

	while(first[i] == '\0' || second[i] != '\0')
	{
		if(first[i] !=	second[i])
		{
			flag = *first - *second;
			break;
		}
		++i;
	}
	return flag;

	/*for(i = 0;; ++i)
	{
		if((first[i] > second[i]) || (first[i] != '\0' && second[i] == '\0'))
		{
			flag = 1;
			break;
		}		
		else if((first[i] < second[i]) || (first[i] == '\0' && second[i] != '\0'))
		{
			flag = -1;
			break;
		}
	}
	return flag;*/
}

void my_strcpy(char* dest, char* source)
{
	int i = 0;	

	while(source[i] != '\0')
	{
		dest[i] = source[i];
		++i;
	}
	dest[i] = '\0';
}

void my_strcat(char* dest, char* source)
{
	int i = 0, j = 0;	

	while(dest[i] != '\0')
	{		
		++i;
	}

	while(source[j] != '\0')
	{		
		dest[i] = source[j];
		++i;
		++j;
	}

	dest[i] = '\0';
}

int main(){
	char s1[32];
	char s2[32];

	char dest[32];
	char source[32];

	printf("Enter first string: ");
	scanf("%s", s1);

	printf("Enter second string: ");
	scanf("%s", s2);
	
	printf("Result strcmp: %d\n", my_strcmp(s1, s2));		

	/*printf("Enter string to copy: ");
	scanf("%s", source);
	
	my_strcpy(dest, source);
	printf("Result strcpy: %s\n", dest);
	
	printf("Enter dest string: ");
	scanf("%s", dest);

	printf("Enter source string: ");
	scanf("%s", source);

	my_strcat(dest, source);
	printf("Result strcat: %s\n", dest);*/

	return 0;
}
