/*COP3502C Mideterm Assignment One
This program is written by: Maria Corella*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
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
int isBalancedParenthesis(char *c);//Function b
char* convertToPostfix(char *c);
int evaluate(char *c);
char* menu (void);//Function a
int isOperator (char c);//Function c
int calculate (int a, int b, char op);//Function f
int getOperatorPriority (char c);//Function d
int convertToInt (char c);//Function e
int correctWhitespace(char *c);
void append(char* s, char c);

//Requirement 2. Main function.
int main(){

	char *str, *postfix;//New line #1.
	
	while(strcmp(str = menu(), "exit")!=0){
		if (isBalancedParenthesis(str)){
			if (correctWhitespace(str)){//New line #3.
				postfix = convertToPostfix(str);
				printf("\nConverted to postfix: %s\n", postfix);//New line #4
				printf("\nAnswer is: %d\n", evaluate(postfix));//New line #5
			}
		}
		else{
			printf("\nParenthesis imbalanced\n");
			break;//New line #6
		}
	break;//New line #7
	}
	free(str);	
	return 0;	
}

//Initializes stack.
void initialize(struct stack *stackPtr) {
     stackPtr->top = -1;
}

// Returns true if the stack pointed to by stackPtr is full.
int isFull(struct stack *stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

//Returns 1 if completed, 0 otherwise.
int push(struct stack *stackPtr, char value) {
    // Check if the stack is full.
    if (isFull(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->stack[stackPtr->top + 1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true if the stack pointed to by stackPtr is empty.
int isEmpty(struct stack *stackPtr) {
    return (stackPtr->top == -1);
}

//Returns -1 if incomplete. Returns the char if complete.
char pop(struct stack *stackPtr) {
    char value;

    if (isEmpty(stackPtr)){
        return EMPTY;
    }

    value = stackPtr->stack[stackPtr->top];
    (stackPtr->top)--;
    return value;
}

//Returns char at the top without removing it. Returns -1 if incomplete.
char peek(struct stack *stackPtr) {
    if (isEmpty(stackPtr))
        return EMPTY;
    return stackPtr->stack[stackPtr->top];
}

//Returns 1 if parenthesis are balanced. Returns 0 otherwise.
int isBalancedParenthesis(char *c){
	int i;
	struct stack stackP;
	initialize(&stackP);
	
	for(i = 0; i < strlen(c); i++){
		if (c[i] == '('){
			push(&stackP, c[i]);
		}
		else if (c[i] == ')'){
			if (peek(&stackP) == '('){
				pop(&stackP);
			}
			else {
				return 0;
			}
		}
	}
	
	//Checks that stack is empty.
	if (isEmpty(&stackP) == 0)
		return 0;
	
	return 1;
}

//Converts infix string to postfix. Returns postfix string pointer.
char* convertToPostfix(char *c){
	int i, counter = 0;
	struct stack opStack;
	initialize(&opStack);
	char trash;
	
	for (i = 0; i < strlen(c); i++){
		//If current char is an operator, analize.
		if (isOperator(c[i]) == 1){
			if (getOperatorPriority(peek(&opStack)) == -1){//If operator in stack is parenthesis.
				push(&opStack, c[i]);
			}
			//While operator at top of stack has higher or equal priority to the current operator, pop until current operator has highest priority.
			else if (getOperatorPriority(c[i]) <= getOperatorPriority(peek(&opStack))){
				while (getOperatorPriority(c[i]) <= getOperatorPriority(peek(&opStack))){
					append(postfix, pop(&opStack));
					append(postfix, ' ');
				}
				push(&opStack, c[i]);
			}
			//If current operator has higest priority, push to stack.
			else if (getOperatorPriority(c[i]) > getOperatorPriority(peek(&opStack))){
				push(&opStack, c[i]);
			}
		}
		
		//If current char is open parenthesis, push to stack.
		else if(c[i] == '('){
			push(&opStack, c[i]);
		}
		
		//If current char is closed parenthesis. Pop stack until open parenthesis.
		else if(c[i] == ')'){
			while (peek(&opStack) != '('){
				append(postfix, pop(&opStack));
				append(postfix, ' ');
			}
			trash = pop(&opStack);//Pop open paranthesis.
		}
		
		//If the current char is a number, add to postfix.
		else if (c[i] >= '0' && c[i] <= '9'){
			append(postfix, c[i]);
			if (c[i + 1] != '\0' && isdigit(c[i + 1]) == 0){
				append(postfix, ' ');
			}
		}
	}
	
	//After reading input is done. Pop the stack
	while (isEmpty(&opStack) != 1){
		append(postfix, ' ');
		append(postfix, pop(&opStack));
	}
	

	return postfix;
		
}

//Evaluates postfix string. Returns an int answer.
int evaluate(char *c){
	int i, top = -1, a, b, result, multNumb, size;
	int eval[50];
	char op;
	
	for (i = 0; i < strlen(c); i++){
		if (isdigit(c[i])){
			//Checks if the next char in the stack is a digit. Takes care of 2+ digit numbers.
			if(c[i + 1] != '\0'){
				if (i > 0){
					//If the previous char was a digit then it wont evaluate.
					if (isdigit(c[i - 1]) != 0){
						continue;
					}
					//If the previous digit was anything else, it'll use atoi to convert the multiple chars to a single int and store it in the int stack.
					else {
						multNumb = atoi(&c[i]);
						eval[++top] = multNumb;	
					}
				}
				//If this is the first element in the string then use atoi to convert multiple chars to a single int and store it in the int stack
				else {
					multNumb = atoi(&c[i]);
					eval[++top] = multNumb;
				}
			}
			//If the next char in the string isnt an int then convert the current char to an int and add to the stack.
			else{
				eval[++top] = convertToInt(c[i]);
			}
		}
		//If the element in the string is a space then ignore.
		else if(c[i] == ' '){
			continue;
		}
		
		//If the element is none of the above then its an operator.
		//We pop 2 integers from the stack and evaluate them using the operator.
		else {
			a = eval[top--];
			b = eval[top--];
			result = calculate(a, b, c[i]);
			eval[++top] = result;
		}
	}
	//Returns the first element in the stack which is also the answer.
	return eval[0];
}

//Asks for input. Returns a string with the input. Will exit if the input is 'x'.
char* menu(){
	
	char c, d;
	char infix[50];
	char *string;

	printf("Menu:\n");
	printf("Enter 'e' to enter an infix. Enter 'x' to exit the program.\n");
	scanf("%c", &c);
	if (c == 'x'){
		printf("Exiting program\n");
		string = (char *)malloc(sizeof(char) * 5);
		strcpy(string, "exit");
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
		string = (char *)malloc(sizeof(char) * 5);
		strcpy(string, "exit");
		
	}
}

//Returns 1 if the char is an accepted operator.
int isOperator(char c){
	if (c == '^' || c == '+' || c == '-' || c == '/' || c == '*' || c == '%'){
		return 1;
	}
	else
		return 0;
}

//Takes 2 integers and an operator and preforms the operation. Returns an int answer to that operation.
int calculate (int a, int b, char op){
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
	if (isOperator(c)){
		if (c == '^'){
			return 3;
		}
		else if (c == '*' || c == '/' || c == '%'){
			return 2;
		}
		else if (c == '+' || c == '-'){
			return 1;
		}
	}
	else {
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

//Checks the string to ensure the string has correct whitespace. Returns 1 if it is. Returns 0 otherwise.
int correctWhitespace(char *c){	
	int i;
	
	for(i = 0; i < strlen(c) - 2; i++){
		if (c[i] >= '0' && c[i] <= '9'){
			if (c[i + 1] == ' '){
				if (c[i + 2] >= '0' && c[i + 2] <= '9'){
					printf("Incorrect whitespace.\n");
					return 0;
				}
			}
		}
	}
	return 1;
}

//Used to append a char to a string.
void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
