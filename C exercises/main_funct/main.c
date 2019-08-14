#include <stdio.h>
#include <string.h>


int isNumber(char* number)
{
	int i, result = 1;

	for(i = 0; i < strlen(number); ++i)
	{
		if(!isdigit(number[i]))
		{
			result = 0;
			break;
		}
	}

	return result;
}

int isString(char* string)
{
	int i, result = 1;

	for(i = 0; i < strlen(string); ++i)
	{
		if(!isalpha(string[i]))
		{
			result = 0;
			break;
		}
	}

	return result;
}


int main(int argc, char* argv[])
{
	char *age, *name;
	int flag_success = 0;
	
	if(argc != 3)
	{
		printf("Parameters is incorrect\n");
		return 0;
	}

	if(isNumber(argv[1]) && isString(argv[2]))
	{
		age = argv[1];
		name = argv[2];
		flag_success = 1;
	}
	else if(isNumber(argv[2]) && isString(argv[1]))
	{
		age = argv[2];
		name = argv[1];
		flag_success = 1;		
	}
	
	if(flag_success)
	{
		printf("Parameters is correct\n");
		printf("%s %s\n", age, name);
	}
	else
	{
		printf("Parameters is incorrect\n");
	}	

	return 0;
}
