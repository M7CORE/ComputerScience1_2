/*COP 3502C Midterm Assignment Two
This program is writter by: Maria Corella*/

#include<stdio.h>
#include<stdlib.h>

//struct for double linked list.
typedef struct soldier{
	int data;
	struct soldier *next;
	struct soldier *previous;
}soldier;

soldier* create_soldier(int sequence);//Function a
soldier* create_reverse_circle(int n);//Function b
soldier* rearrange_circle(soldier* head);//Function c
void display(soldier* head);//Function d
int kill(soldier* head, int n, int k);//Function e

int main(){
	int n, k;
	soldier* head = NULL;
	
	printf("Enter the total number of people: ");
	scanf("%d", &n);
	printf("\nEnter the position of the person killed: ");
	scanf("%d", &k);
	printf("\n");
	head = create_reverse_circle(n);
	struct soldier *ptr = head;
	printf("p: %d, c: %d, n:%d\n", ptr->previous->data, ptr->data, ptr->next->data);
	ptr = ptr->next;
	printf("p: %d, c: %d, n:%d\n", ptr->previous->data, ptr->data, ptr->next->data);
	ptr = ptr->next;
	printf("p: %d, c: %d, n:%d\n", ptr->previous->data, ptr->data, ptr->next->data);
	ptr = ptr->next;
	printf("p: %d, c: %d, n:%d\n", ptr->previous->data, ptr->data, ptr->next->data);
	ptr = ptr->next;
	printf("p: %d, c: %d, n:%d\n", ptr->previous->data, ptr->data, ptr->next->data);
	ptr = ptr->next;
	printf("p: %d, c: %d, n:%d\n", ptr->previous->data, ptr->data, ptr->next->data);
	ptr = ptr->next;
	printf("p: %d, c: %d, n:%d\n", ptr->previous->data, ptr->data, ptr->next->data);
	ptr = ptr->next;
	head = rearrange_circle(head);
	printf("The safe position is: %d\n", kill(head, n, k));
	
	return 0;
}

int kill(soldier* head, int n, int k){
	soldier *kill = head;
	soldier *printPtr;
	int i;
	
	while (head->next != head){
		for (i = 0; i < k - 1; i++){
			kill = kill->next;
		}
		
		kill->previous->next = kill->next;
		kill->next->previous = kill->previous;
		head = kill->next;
		free(kill);
		kill = head;
	}
	
	return kill->data;
}

//Creates a linked list of size n. Returns head of list. Formed in descending order.
soldier* create_reverse_circle(int n){
printf("Reverse circle...\n");
//	soldier *ptr, *newsold, *head, *news;
	soldier *ptr, *newsold, *head;
	int i;
	
	for (i = n; i > 0; i--){
		//First node of the linked list special case.
		if (i == n){
			newsold= create_soldier(i);
			newsold->next = newsold;
			newsold->previous = newsold;
			head = newsold;
			ptr = newsold;
		}
		//Other nodes after first node.
		else{
			newsold = create_soldier(i);
			newsold->next = head;
			head->previous = newsold;
			ptr->next = newsold;
			newsold->previous = ptr;
			ptr = ptr->next;
		}
	}
	display(head);
	printf("\n");
	return head;
}

//Creates a soldier linked list element and initializes it's values and data to be stored.
soldier* create_soldier(int sequence){
	soldier* newsoldier = (soldier *)malloc(sizeof(soldier));
	newsoldier->data = sequence;
	newsoldier->next = NULL;
	newsoldier->previous = NULL;
	return newsoldier;
}

//Reverses linked list to ascending order.
soldier* rearrange_circle(soldier* head){
	
	struct soldier *current;
	struct soldier *temp;
	
	current = head;
	
	while (current->next != head){
		temp = current->next;
		current->next = current->previous;
		current->previous = temp;
		current = temp;
	}
	
	temp = current->next;
	current->next = current->previous;
	current->previous = temp;
	
	head = current;
	
/*	soldier* ptr = head;
	int n = head->data;
	int i;
	
	for (i = 0; i < n - 1; i++){
		ptr->previous->next = ptr->previous->previous;
		ptr->previous->previous = ptr;
		ptr = ptr->next;
	}
	
	ptr->next->next = ptr->next->previous;
	ptr->next->previous = ptr;
	head = head->next;
*/	
	printf("Rearranged circle...\n");
	display(head);
	printf("\n");
	return head;
	
}

void display(soldier* head){
	int i, n;
	soldier* ptr = head;
	
	if (head->data == 1)
		n = head->previous->data;
	else
		n = head->data;
		
	for (i = 0; i < n; i++){
		printf("%d->", ptr->data);
		ptr = ptr->next;
	}
	
	printf("Back to %d\n", ptr->data);
}

