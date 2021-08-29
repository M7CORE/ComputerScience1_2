//Lab 5
//Maria Corella
//Queue Linked List

#include<stdio.h>
#include<stdlib.h>

//Node struct
struct node{
	int data;
	struct node *next;
};

struct queue{
	struct node* headPtr;
	struct node* tailPtr;
};

//Function prototypes
void init(struct queue* list);//function 1
void enqueue(struct queue* q, int data);//Function 2
void dequeue(struct queue* q);//Function 3
int front(struct queue* q);//Function 4
int isEmpty(struct queue* list);//Function 5
int menu();//Custom function to display menu
void display();//Custom function to display queue



int main(){
	int value, data;
	struct queue *newQueue = (struct queue *)malloc(sizeof(struct queue));
	init(newQueue);
	
	while((value = menu()) != 3){
		if (value == 1){
			printf("Enter data to enqueue: ");
			scanf ("%d", &data);
			enqueue(newQueue, data);
			display(newQueue);
			printf("\n");
		}
		
		else if(value == 2){
			if (!(isEmpty(newQueue))){
				dequeue(newQueue);
				display(newQueue);
				printf("\n");
			}
			else if (isEmpty(newQueue))
				printf("Queue is empty\n\n");
		}
		
		else
			printf("Incorrect entry\n");
	}
	
	return 0;
}

void dequeue(struct queue* q){
	struct node *ptr;
	
	//part a
	ptr = q->headPtr;
	
	//part b
	q->headPtr = q->headPtr->next;
	
	//Part c
	free(ptr);
}

void enqueue(struct queue* q, int data){
	//Part a
	struct node *newPtr;
	newPtr = (struct node*)malloc(sizeof(struct node));
	newPtr->data = data;
	newPtr->next = NULL;
	
	//If the queue is empty
	if (isEmpty(q)){
		q->headPtr = newPtr;
	}
	
	//part b
	else {
		q->tailPtr->next= newPtr;
	}
	
	//Part c
	q->tailPtr = newPtr;
}

int menu(){
	int value;
	
	printf("Enter 1 to enqueue, 2 to dequeue, 3 to exit program\n");
	printf("Selection: ");
	scanf("%d", &value);
	
	return value;
}

void display(struct queue* q){
	struct node *t = q->headPtr;
	
	if (t == NULL)
		printf("Queue is empty.\n");
	else{
		printf("Queue: ");
	}
	while (t != NULL){
		printf("%d -> ", t->data);
		t = t->next;
	}
	printf("NULL\n");

}

void init(struct queue* list){
	list->headPtr = NULL;
	list->tailPtr = NULL;
}

int isEmpty(struct queue* list){
	if (list->headPtr == NULL && list->tailPtr == NULL)
		return 1;
	return 0;
}

int front(struct queue* q){
	return q->headPtr->data;
}
