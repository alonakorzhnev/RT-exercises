#include <stdio.h>

int order(int n);

int order(int n){
	int temp = n%10, flag = 1;

	while(n/10 > 0){
		n /= 10;
		if(temp < n%10){
			flag = 0;
			break;
		}
		temp = n%10;
	} 
	return flag;
}

int main(){
	int number;
	
	printf("Please enter number: ");
	scanf("%d", &number);
	
	printf("Result: %d\n", order(number));

	return 0;
}
