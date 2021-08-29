//Lab #4
//Simulate call center queue system
//Maria Corella
#include<stdio.h>
#define INIT_SIZE 6

struct queue {
    struct customer *elements;
    int front;
    int numElements;
    int queueSize;
};

typedef struct Customer{
	int account_no;
	char name[100];
} customer;

void init(struct queue* qPtr);
void enqueue(struct queue* qPtr);
void dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
void displayQueue(struct queue *qptr);
char ranSelect();
int front(struct queue* qPtr);

int main(){
	
	struct queue *myqPtr = (struct queue*)malloc(sizeof(struct queue));
	init(myqPtr);
	
	while(1){
		if (ranSelect() == 'c'){
			printf("Customer is trying to call...\n");
			enqueue(myqPtr);
			display(myqPtr);
		}
		else if (ranSelect() == 's'){
			printf("Customer is trying to call...\n");
			enqueue(myqPtr);
			display(myqPtr);
		}	
		else 
			printf("Problem with ranSelect return.\n");
	}
	
}

void init(struct queue* qPtr) {

     qPtr->elements = (int*)malloc(sizeof(struct customer)*INIT_SIZE);
     qPtr->front = 0;
     qPtr->numElements = 0;
     qPtr->queueSize = INIT_SIZE;
}

int enqueue(struct queue* qPtr) {

    int i;

    if (qPtr->numElements != qPtr->queueSize) {
    	int acc, newpos;
    	char name[50] ,c;
    	newpos = (qPtr->front+qPtr->numElements)%qPtr->queueSize;
    	printf("Thank you for the call, please enter account number:");
    	scanf("%d", &acc);
    	qPtr->elements[newpos].account_no = acc;
    	printf("Please enter your name:");
    	scanf("%[^\n]s", name);
    	strcpy(qPtr->elements[newpos].name, name);
        (qPtr->numElements)++;

        return 1;
    }

    else {
    	printf("Maximum capacity reached, call at a later time\n");
    }
    
    displayQueue(qPtr);

}

void dequeue(struct queue* qPtr) {

    if (empty(qPtr)){
    	printf("No customers in line, queue is empty\n");
	}
	
	else{
		printf("Serving next customer...\n");
		printf("Customer served: %d, %s", qptr->elements[qPtr->front].account_no, qptr->elements[qPtr->front].name);
		qPtr->front = (qPtr->front + 1)% qPtr->queueSize;

    	(qPtr->numElements)--;
	}
}

int empty(struct queue* qPtr) {
    return qPtr->numElements == 0;
}

/*
int front(struct queue* qPtr) {
    if (qPtr->numElements != 0)
        return qPtr->elements[qPtr->front];
    else
        return EMPTY;
}
*/

char ranSelect(){
	
	char[2] = {'c', 's'};
	srand(time());
	return char[rand()%2];
}

void displayQueue(struct queue *qPtr){
	int i;
	
	printf("Current queue...\n");
	if(empty(qPtr)){
		printf("Queue is empty\n");
	}
	
	else if(qPtr->front+qPtr->numElements < qPtr->queueSize){
		for (i = qPtr->front; i < qPtr->numElements+qPtr->front; i++){
		printf("%d - %s %d",i + 1, qptr->elements[i].name, qptr->elements[i].account_no);
		}
	}
	
	else{
		for (i = qPtr->front; i < qPtr->queueSize; i++){
		printf("%d - %s %d",i + 1, qptr->elements[i].name, qptr->elements[i].account_no);
		}
		for(i = 0; i <(qPtr->front+qPtr->numElements)%qPtr->queueSize; i++){
			
		}
	}
	
}
