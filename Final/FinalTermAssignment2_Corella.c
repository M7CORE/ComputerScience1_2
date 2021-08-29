/* COP 3502C Final Term Assignment 2
This program is written by: Maria Corella */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node{
	char name[20];
	struct node *left;
	struct node *right;
}node;

//Print functions
void inorder (node *p, FILE* out);
void preorder(node *p, FILE* out);
void postorder (node *p, FILE* out);

//Functions used to create the tree
node* insert(node* root, node* element);//Inserts node in corresponding place.
node* createNode(char name[]);//Creates a node
node* buildTree(FILE *in, int n, node* rootNode);//Creates tree by creating and inserting nodes.

//Functions used to search/iterate the tree
void searchTree(node* rootNode, int s, FILE* in, FILE* out);//Searches the tree for the names from the text.
node* findNode (node* current, char name[]);//Finds a node given the data.

//Aux functions
int height(node* rootNode);
node* minVal (node* rootNode);
node* maxVal (node* rootNode);
int isLeaf(node* currentNode);
int hasOnlyLeftChild (node* currentNode);
int hasOnlyRightChild (node* currentNode);
node* findParentNode(node *currentNode, node* rootNode);
int leftHeight (node* rootNode);
int rightHeight (node* rootNode);

//Functions for the assignment
int totalCharacters (node *p);
int countBefore (node* root, char name[]);
int isBalanced (node* rootNode, FILE *out);

//Functions for the delete phase
int deletePhase (node* rootNode, FILE *in, int d, FILE* out);//Deletes the names that were included in the text.
node* deleteNode (node* current, node* rootNode);//Deletes a specific node from the tree.

int main(){
	int n, s, d;
	node *rootNode = NULL;
	
	FILE *in, *out;
	in = fopen("in.txt", "r");
	out = fopen("out.txt", "w");
	
	fscanf(in, "%d %d %d", &n, &s, &d);
	
	rootNode = buildTree(in, n, rootNode);
	
	fprintf(out, "Preorder: ");
	printf("Preorder: ");
	preorder(rootNode, out);
	fprintf(out, "\n");
	printf("\n");
	
	fprintf(out, "Inorder: ");
	printf("Inorder: ");
	inorder(rootNode, out);
	fprintf(out, "\n");
	printf("\n");
	
	fprintf(out, "Postorder: ");
	printf("Postorder: ");
	postorder(rootNode, out);
	fprintf(out, "\n");
	printf("\n");
	
	printf("Total characters: %d\n", totalCharacters(rootNode));
	fprintf(out, "Total characters: %d\n", totalCharacters(rootNode));
	
	printf("Height left = %d, height right = %d. ", height(rootNode->left) - 1, height(rootNode->right) - 1);
	
	if (isBalanced(rootNode, out)){
		printf("The tree is balanced.\n");
		fprintf(out, "The tree is balanced.\n");
	}
	else{
		printf("The tree is imbalanced.\n");
		fprintf(out, "The tree is imbalanced.\n");
	}
	
	printf("Search Phase:\n");
	fprintf(out, "Search Phase:\n");
	searchTree(rootNode, s, in, out);
	
	printf("Delete Phase:\n");
	fprintf(out, "Delete Phase:\n");
	deletePhase(rootNode, in, d, out);
	fprintf(out, "Inorder: ");
	printf("Inorder: ");
	inorder(rootNode, out);
		
	fclose(in);
	fclose(out);
	
	return 0;
}

node *buildTree(FILE *in, int n, node* rootNode){
	int i;
	char temp[20];
	node* tempNode;
	
	for(i = 0; i < n; i++){
		fscanf(in, "%s", temp);
		tempNode = createNode(temp);
		rootNode = insert(rootNode, tempNode);
	}
	return rootNode;	
}

node* insert(node* rootNode, node* element){
	if (rootNode == NULL)
		return element;
	else{
		//element greater than root
		if (strcmp(element->name, rootNode->name) > 0){
			if (rootNode->right != NULL)
				rootNode->right = insert(rootNode->right, element);
			else
				rootNode->right = element;
		}
		else{
			if (rootNode->left != NULL)
				rootNode->left = insert(rootNode->left, element);
			else
				rootNode->left = element;
		}
		return rootNode;
	}
}

node* createNode(char name[]){
	node* temp = (node*)malloc(sizeof(node));
	
//	temp->name = name;
	strcpy(temp->name, name);
	temp->left = NULL;
	temp->right = NULL;
	
	return temp;
}

void searchTree(node* rootNode, int s, FILE* in, FILE* out){
	int i;
	char temp[20];
	
	for (i = 0; i < s; i++){
		fscanf(in, "%s", temp);
		if (findNode (rootNode, temp) != NULL){
			printf("%s: Found, Items before: %d\n", temp, countBefore(rootNode, temp));
			fprintf(out, "%s: Found, Items before: %d\n", temp, countBefore(rootNode, temp));
		}
		else {
			fprintf(out, "%s: Not found, Items before: 0\n", temp);
			printf("%s: Not found, Items before: 0\n", temp);
		}	
	}
}

node* findNode (node* current, char name[]){

	if (current != NULL){
		if (strcmp(current->name, name) == 0)
			return current;
		if (strcmp(current->name, name) > 0)
			return findNode (current->left, name);
		else 
			return findNode (current->right, name);
	}
	else
		return NULL;
}

void preorder(node *p, FILE* out){
	if (p != NULL){
		printf("%s ", p->name);
		fprintf(out, "%s ", p->name);
		preorder(p->left, out);
		preorder(p->right, out);
	}
}

void inorder (node *p, FILE* out){
	if (p != NULL){
		inorder(p->left, out);
		printf("%s ", p->name);
		fprintf(out, "%s ", p->name);
		inorder(p->right, out);
	}
}

void postorder (node *p, FILE* out){
	if (p != NULL){
		postorder(p->left, out);
		postorder(p->right, out);
		printf("%s ", p->name);
		fprintf(out, "%s ", p->name);
	}	
}

int height(node* rootNode){
	int left, right;
	
	if (rootNode == NULL){
		return 0;
	}
	
	left = height(rootNode->left);
	right = height(rootNode->right);
	
	if (left > right)
		return left + 1;
	
	return right + 1;
}

int isBalanced (node* rootNode, FILE* out){
	int left, right;
	
	if (rootNode == NULL)
		return 1;
	
	left = height(rootNode->left);
	right = height(rootNode->right);

	if (isBalanced(rootNode->left, out) && isBalanced(rootNode->right, out) && abs(left - right) <= 1)
		return 1;
	return 0;
}

int totalCharacters (node *p){
	if (p == NULL)
		return 0;
	return strlen(p->name) + totalCharacters(p->left) + totalCharacters(p->right);	
}

int deletePhase (node* rootNode, FILE* in, int d, FILE* out){
	int i;
	char temp[20];
	node* parentNode = NULL;
	node* delNode = NULL;
	
	for (i = 0; i < d; i++){
		fscanf(in, "%s", temp);
		if (delNode = findNode(rootNode, temp)){
			if (deleteNode(delNode, rootNode) != NULL){
				printf("%s: deleted\n", temp);
				fprintf(out, "%s: deleted\n", temp);
			}
			
		}
	}	
}

node* deleteNode (node* delNode, node* rootNode){
	
	node *newDelNode, *saveNode, *parent;
	char saveName[20];
	
	parent = findParentNode(delNode, rootNode);
	
	if (isLeaf(delNode)){
		if (parent == NULL){
			free(rootNode);
			return NULL;
		}
		
		if (strcmp(parent->name, delNode->name) > 0){
			free(parent->left);
			parent->left = NULL;
		}
		
		else {
			free(parent->right);
			parent->right = NULL;
		}
		
		return rootNode;
	}
	
	if (hasOnlyLeftChild(delNode)){
		if (parent == NULL){
			saveNode = delNode->left;
			free (delNode);
			return saveNode;
		}
		
		if (strcmp(parent->name, delNode->name) > 0){
			saveNode = parent->left;
			parent->left = parent->left->left;
			free(saveNode);
		}
		
		else {
			saveNode = parent->right;
			parent->right = parent->right->left;
			free(saveNode);
		}
		return rootNode;
	}
	
	if (hasOnlyRightChild(delNode)){
		if (parent == NULL){
			saveNode = delNode->right;
			free(delNode);
			return saveNode;
		}
		
		if (strcmp(parent->name, delNode->name) > 0){
			saveNode = parent->left;
			parent->left = parent->left->right;
			free(saveNode);
		}
		
		else {
			saveNode = parent->right;
			parent->right = parent->right->right;
			free(saveNode);
		}
		return rootNode;
	}
	
	//new delete node is equal to the max val to the left
	newDelNode = maxVal(delNode->left);
	
	//copy the name of the new delete node into the saveName 
	strcpy(saveName, newDelNode->name);
	
	//delete the newDelNode
	deleteNode(newDelNode, rootNode);
	
	//copy name from 
	strcpy(delNode->name, saveName);
	
	return rootNode;
}

node* findParentNode(node *currentNode, node* rootNode){
	
	if (currentNode == NULL || rootNode == currentNode)
		return NULL;
	else if (rootNode->left == currentNode || rootNode->right == currentNode)
		return rootNode;
	else if (strcmp(rootNode->name, currentNode->name) > 0)
		return findParentNode(currentNode, rootNode->left);
	else if (strcmp(rootNode->name, currentNode->name) < 0)
		return findParentNode (currentNode, rootNode->right);
	return NULL;
	
}

node* minVal (node* rootNode){
	if (rootNode->left == NULL)
		return rootNode;
	else
		return minVal(rootNode->left);
}

node* maxVal (node* rootNode){
	if (rootNode->right == NULL)
		return rootNode;
	else
		return maxVal(rootNode->right);
}

int isLeaf(node* currentNode){
	
	return (currentNode->left == NULL && currentNode->right == NULL);
	
}

int hasOnlyLeftChild (node* currentNode){
	
	return (currentNode->left != NULL && currentNode->right == NULL);
	
}

int hasOnlyRightChild (node* currentNode){
	
	return (currentNode->left == NULL && currentNode->right != NULL);	
	
}

int countBefore (node* rootNode, char name[]){
	int count = 0;
	if (rootNode == NULL)
		return 0;
	else if (strcmp(rootNode->name, name) < 0){
		count++;
		count += countBefore(rootNode->left, name);
		count += countBefore(rootNode->right, name);
	}
	else
		count += countBefore(rootNode->left, name);
		
	return count;
}


