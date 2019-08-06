#include <stdio.h>

int reverse(int n);

int reverse(int n){
	int temp = n, reverse = 0, flag = 0;
	
	while(temp != 0){
		reverse = reverse*10 + temp%10;
		temp/=10;
	}

	return reverse;	
}

int main(){
	int number;
	
	printf("Please enter number: ");
	scanf("%d", &number);
	
	printf("Result: %d\n", reverse(number));

	return 0;
}
