#include <stdio.h>

int polindrome(int n);

int polindrome(int n){
	int temp = n, reverse = 0, flag = 0;
	
	while(temp != 0){
		reverse = reverse*10 + temp%10;
		temp/=10;
	}

	if(n == reverse){
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
	
	printf("Result: %d\n", polindrome(number));

	return 0;
}
