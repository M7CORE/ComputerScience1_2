#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function header
int toBaseTen(char string[], int base);
int power(int base, int exponent);

int main(){
	char userString[20];
	int base, decimal;
	printf("Enter string: ");
	scanf("%20s", userString);//Get string
	printf("Enter base: ");
	scanf("%d", &base);//Get base
	decimal = toBaseTen(userString, base);
	printf("\n%s base %d in decimal is %d\n", userString, base, decimal);
}

//Converts string to base 10(Decimal)
int toBaseTen(char string[], int base){
	int length, temp, i, decimal = 0;
	length = strlen(string);//Get length of string
	for(i = 0; i < length; i++){//iterate through string to analyze each char
		if ((string[i] >= '0') && (string[i] <= '9')){//Will execute if char is number
			temp = (string[i]) - '0';	
		}
		else if ((string[i] >= 'A') && (string[i] <= 'Z')){//Will execute if char is uppercase letter
			temp = (((string[i]) - 'A') + 10);
			temp = ("%d\n", temp);
		}
		else //will execute if char is not an accepted char
			("%c can't be converted to decimal.\n", string[i]);
		decimal = decimal + (temp * power(base, (length - i - 1)));
	}
	return decimal;
}

//Raises base to power exponent
int power(int base, int exponent){
	int i;
	int result = 1;
	for (i = exponent; i > 0; i--){
		result = result * base;
	}
	return result;
}
