#include <stdio.h>

int prime(int n);

int prime(int n){
	int i, flag = 1;
	
	for(i = 2; i < n; ++i){
		if(n%i == 0){
			flag = 0;
			break;
		}	
	}
	return flag;	
}

int main(){
	int number;
	
	printf("Please enter number: ");
	scanf("%d", &number);
	
	printf("Result: %d\n", prime(number));

	return 0;
}
