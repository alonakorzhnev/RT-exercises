#include <stdio.h>

void func1(int n);
void func2(int n);
void func3(int n);

void func1(int n){
	int rows, stars;
	
	for(rows = 1; rows <= n; ++rows){
		for(stars = 0; stars < rows; ++stars){
			printf("*");
		}
		
		printf("\n");
	}

	printf("\n");	
}

void func2(int n){
	int rows, stars;
	
	for(rows = 1; rows <= n; ++rows){
		for(stars = 0; stars < rows; ++stars){
			printf("*");
		}
		
		printf("\n");
	}

	for(rows = rows - 2; rows >= 1; --rows){
		for(stars = 0; stars < rows; ++stars){
			printf("*");
		}
		
		printf("\n");
	}

	printf("\n");
}

void func3(int n){
	int rows, blanks, stars;

	for(rows = 0; rows < n; ++rows){
		for(blanks = rows; blanks < n; ++blanks){
			printf(" ");
		}
		for(stars = n; stars >= n - (2*rows); --stars){
			printf("*");		
		}
		printf("\n");		
		
	}

	printf("\n");
}


int main(){
	int number;
	
	printf("Please enter N value: ");
	scanf("%d", &number);
	
	func1(number);
	func2(number);
	func3(number);

	return 0;
}
