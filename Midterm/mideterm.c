/*COP3502C Mideterm Assignment One
This program is written by: Maria Corella*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 50
#define EMPTY -1

//Global char array for postfix.
char postfix[50] = {'\0'};

//Requirement 1. Creates and uses stack.
struct stack{
	
	char stack[SIZE];
	int top;
};

//Function headers.
void initialize (struct stack *stackPtr);
int isFull(struct stack *stackPtr);
int push(struct stack *stackPtr, char value);
int isEmpty(struct stack *stackPtr);
char pop(struct stack *stackPtr);
char peek(struct stack *stackPtr);
int isBalancedParenthesis(char *c);
char* convertToPostfix(char *c);
int evaluate(char *c);
char* menu (void);
int isOperator (char c);
int calculate (int a, int b, char op);
int getOperatorPriority (char c);
int convertToInt (char c);
int correctWhitespace(char *c);
void append(char* s, char c);

//Requirement 2. Main function.
int main(){

	char *str, *postfix;//New line #1.
	int answer = -1;//New line #2.
	
//	printf("Start of main()\n");
	while(strcmp(str = menu(), "exit")!=0){
	//	printf("Entry is not x. Checking parenthesis balance.\n");
	//	printf("%c", str);
		if (isBalancedParenthesis(str)){
	//		printf("Parenthesis is balanced. Checking whitespace.\n");
			if (correctWhitespace(str)){//New line #3.
	//			printf("Correct whitespace. Converting to postfix.\n");
				postfix = convertToPostfix(str);
				printf("\nConverted to postfix: %s\n", postfix, strlen(postfix));//New line #4
	//			answer = evaluate(postfix);
				printf("\nAnswer is: %d\n", evaluate(postfix));//New line #5
			}
		}
		else{
			printf("\nParenthesis imbalanced\n");
			break;
		}
	break;
	}	
	return 0;	
}

//Initializes stack.
void initialize(struct stack *stackPtr) {
//	printf("Stack initialized.\n");
     stackPtr->top = -1;
}

// Returns true if the stack pointed to by stackPtr is full.
int isFull(struct stack *stackPtr) {
//	printf("Checking isFull\n");
    return (stackPtr->top == SIZE - 1);
}

//Returns 1 if completed, 0 otherwise.
int push(struct stack *stackPtr, char value) {
//	printf("Pushing into stack\n");
    // Check if the stack is full.
    if (isFull(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->stack[stackPtr->top + 1] = value;
    (stackPtr->top)++;
//    printf("Added value %c to stack at %d\n", stackPtr->stack[stackPtr->top], stackPtr->top);
    return 1;
}

// Returns true if the stack pointed to by stackPtr is empty.
int isEmpty(struct stack *stackPtr) {
//	printf("Checking is empty\n");
    return (stackPtr->top == -1);
}

//Returns -1 if incomplete. Returns the char if complete.
char pop(struct stack *stackPtr) {
//	printf("Popping stack\n");
    char value;

    if (isEmpty(stackPtr)){
        return EMPTY;
    }

    value = stackPtr->stack[stackPtr->top];
    (stackPtr->top)--;
//    printf("Value popped is %c. New top is %d\n", value, stackPtr->top);
    return value;
}

//Returns char at the top without removing it. Returns -1 if incomplete.
char peek(struct stack *stackPtr) {
//	printf("Peek stack.\n");
    if (isEmpty(stackPtr))
        return EMPTY;
//	printf("Item peeked is %c at %d\n", stackPtr->stack[stackPtr->top], stackPtr->top);
    return stackPtr->stack[stackPtr->top];
}

int isBalancedParenthesis(char *c){
//	printf("Checking parenthesis balance function.\n");
	int i;
	struct stack stackP;
	initialize(&stackP);
	
	for(i = 0; i < strlen(c); i++){
		if (c[i] == '('){
//			printf("Open parenthesis found\n");
			push(&stackP, c[i]);
		}
		else if (c[i] == ')'){
//			printf("Closing parenthesis found\n");
			if (peek(&stackP) == '('){
				pop(&stackP);
			}
			else {
//				printf("Imbalanced paranthesis\n");
				return 0;
			}
		}
	}
	
	//Checks that stack is empty.
	if (isEmpty(&stackP) == 0)
		return 0;
	
	return 1;
}

char* convertToPostfix(char *c){
//	printf("Converting to postfix function.\n");
	int i, counter = 0;
	struct stack opStack;
	initialize(&opStack);
	char trash;
	
	for (i = 0; i < strlen(c); i++){
//		printf("item being analized is: %c\n", c[i]);
		if (isOperator(c[i]) == 1){
//			printf("Priority is: %d", getOperatorPriority(c[i]));
			if (getOperatorPriority(peek(&opStack)) == -1){
				push(&opStack, c[i]);
			}
			else if (getOperatorPriority(c[i]) <= getOperatorPriority(peek(&opStack))){
				while (getOperatorPriority(c[i]) <= getOperatorPriority(peek(&opStack))){
					append(postfix, pop(&opStack));
					append(postfix, ' ');
				}
				push(&opStack, c[i]);
			}
			else if (getOperatorPriority(c[i]) > getOperatorPriority(peek(&opStack))){
				push(&opStack, c[i]);
			}
		}
		
		else if(c[i] == '('){
			push(&opStack, c[i]);
		}
		
		else if(c[i] == ')'){
			while (peek(&opStack) != '('){
				append(postfix, pop(&opStack));
				append(postfix, ' ');
			}
			trash = pop(&opStack);
		}
		
		else if (c[i] >= '0' && c[i] <= '9'){
//			printf("%c is digit. Adding to postfix.\n", c[i]);
			append(postfix, c[i]);
//			printf("Postfix is: %s\n", postfix);
			if (c[i + 1] != '\0' && isdigit(c[i + 1]) == 0){
				append(postfix, ' ');
			}
				
//			printf("%c is digit. Adding to postfix.\n", c[i]);
//			append(postfix, c[i]);
//			printf("Postfix is: %s\n", postfix);
		}
	}
	
	//After reading input is done. Pop the stack
	while (isEmpty(&opStack) != 1){
//		printf("Emptying stack...\n");
		append(postfix, ' ');
		append(postfix, pop(&opStack));
//		printf("Partial postfix string: %s\n", postfix);
	}
	
//	printf("Finish postfix string is: %s\n", postfix);
	return postfix;
		
}

int evaluate(char *c){
//	printf("Start evaluating the postfix string\n");
	int i, top = -1, a, b, result, multNumb, size;
	int eval[50];
	char op;
	
//	printf("%s. length is %d\n", c, strlen(c));
	for (i = 0; i < strlen(c); i++){
			if (isdigit(c[i])){
				if(c[i + 1] != '\0' && c[i + 1] != 0){
					if (i > 0){
//						printf("%c\n", c[i-1]);
						if (isdigit(c[i - 1]) != 0){
//							printf("%c\n", c[i-1]);
//							printf("Skip bc previous char was digit\n");
							continue;
						}
						else {
							multNumb = atoi(&c[i]);
//							printf("%d is a digit. Will be added to stack\n", multNumb);
							eval[++top] = multNumb;	
						}
					}
					else {
						multNumb = atoi(&c[i]);
//						printf("%d is a digit. Will be added to stack\n", multNumb);
						eval[++top] = multNumb;
					}
				}
//				else if(i > 0){
//					if(c[i - 1] != 0);
//					continue;
//				}
				else{
//					printf("%c is digit. Will be added to stack\n", c[i]);
					eval[++top] = convertToInt(c[i]);
				}
			}
			
			else if(c[i] == ' '){
				continue;
			}
	
			else {
//				printf("%c is an operator. Calculating and storing answer in the stack.\n", c[i]);
				a = eval[top--];
				b = eval[top--];
//				printf("Passed to calculate function as a: %d  b: %d, and operator: %c\n", a, b, c[i]);
				result = calculate(a, b, c[i]);
//				printf("The result is: %d\n", result);
				eval[++top] = result;
			}
	}
	return eval[0];
}

char* menu(){
	
	char c, d;
	char infix[50];
	char *string;

	printf("Menu:\n");
	printf("Enter 'e' to enter an infix. Enter 'x' to exit the program.\n");
	scanf("%c", &c);
	if (c == 'x'){
		printf("Exiting program\n");
		return "exit";
	}
	else if (c == 'e'){
		printf("Enter input: ");
		scanf("%c", &d);
		scanf("%[^\n]s", infix);
		string = (char *)malloc(sizeof(char) * strlen(infix));
		strcpy(string, infix);
		return string;
	}
	else{
		printf("Incorrect entry, exiting program.\n");
		return "exit";
		
	}
}


int isOperator(char c){
//	printf("Entering isOperator function.\n");
	if (c == '^' || c == '+' || c == '-' || c == '/' || c == '*' || c == '%'){
		return 1;
	}
	else
		return 0;
}

int calculate (int a, int b, char op){
//	printf("Entering calculate function.\n");
	int answer, i; 
	if (op == '+')
		answer = a + b;
	else if (op == '-')
		answer = b - a;
	else if (op == '^'){
		answer = 1;
		for (i = a; i > 0; i--)
			answer = answer * b;	
	}
	else if (op == '/')
		answer = b / a;
	else if (op == '*')
		answer = a * b;
	else if (op = '%')
		answer = a % b;
		
	return answer;			
}

//Returns priority for operator. Highest is 3, lowest is 1.
//Returns 0 if not an accepted operator.
int getOperatorPriority (char c){
//	printf("Entering getOperatorPriority function\n");
	if (isOperator(c)){
		if (c == '^'){
//			printf("Priority 3\n");
			return 3;
		}
		else if (c == '*' || c == '/' || c == '%'){
//			printf("Priority 2\n");
			return 2;
		}
		else if (c == '+' || c == '-'){
//			printf("Priority is 1\n");
			return 1;
		}
	}
	else {
//		printf("Not accepted operator for operator priority");
		return -1;
	}
		
}

//Returns int value or -1 if char can't be converted to int.
int convertToInt (char c){
//	printf("Entering convertToInt function\n");
	if (c >= '0' && c <= '9')
		return c - '0';
	else
		return -1;
	
}

int correctWhitespace(char *c){
	
//	printf("Entering correctWhitespace function\n");
	int i;
	
//	printf("%s with length: %d", c, strlen(c));
	for(i = 0; i < strlen(c) - 2; i++){
		if (c[i] >= '0' && c[i] <= '9'){
//			printf("%c is number\n", c[i]);
			if (c[i + 1] == ' '){
//				printf("%c is space\n", c[i+1]);
				if (c[i + 2] >= '0' && c[i + 2] <= '9'){
//					printf("%c is number\n", c[i+2]);
					printf("Incorrect whitespace.\n");
					return 0;
				}
			}
		}
	}
	return 1;
}

void append(char* s, char c)
{
        int len = strlen(s);
//        printf("%d\n", len);
        s[len] = c;
        s[len+1] = '\0';
}

