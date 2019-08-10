#include <stdio.h>

int perfect(int n);

int perfect(int n){
	int i, sum = 0, flag = 0;
	
	for(i = 1; i < n; ++i){
		if(n%i == 0){
			sum += i;
		}	
	}

	if(sum == n){
		flag = 1;	
	}
	else{
		flag = 0;	
	}

	return flag;
}

int main(){
	int number;
	
	printf("Please enter number: ");
	scanf("%d", &number);
	
	printf("Result: %d\n", perfect(number));

	return 0;
}
