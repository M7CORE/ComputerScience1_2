#include<stdio.h>
#include<stdlib.h>
//Lab Final
//Maria Corella

struct tree_node* insert(struct tree_node *root, struct tree_node *element);
struct tree_node* buildTree(FILE* in);
void inorder(struct tree_node* root);
struct tree_node* create_node(int price, int count);
int totalHouses(struct tree_node* root);
int totalValue(struct tree_node* root);


struct tree_node{
	struct tree_node* left;
	struct tree_node* right;
	int price;
	int count;
};


int main(){
	FILE* in1;
	FILE* in2;
	int n1, n2;
	struct tree_node *tree1, *tree2;
	
	in1 = fopen("in1.txt","r");
	tree1 = buildTree(in1);
	inorder(tree1);
	printf("\n");
	fclose(in1);
	
	in2 = fopen("in2.txt", "r");
	tree2 = buildTree(in2);
	inorder(tree2);
	printf("\n");
	fclose(in2);
	
	printf("Total houses in tree 1: %d\n", totalHouses(tree2));
	printf("Total houses in tree 2: %d\n", totalHouses(tree2));
	
	if (totalHouses(tree1) > totalHouses(tree2)){
		printf("Tree 1 has more houses.\n");
	}
	else
		printf("Tree 2 has more houses.\n");
	
	
	
	
	return 0;
}

struct tree_node* insert(struct tree_node *root, struct tree_node *element) {
	if (root == NULL){
		return element;
	}
	else {
		// element should be inserted to the right.
		if (element->price > root->price) {
			// There is a right subtree to insert the node.
			if (root->right != NULL)
				root->right = insert(root->right, element);
			// Place the node directly to the right of root.
			else
				root->right = element;
		}
		// element should be inserted to the left.
		else {
			// There is a left subtree to insert the node.
			if (root->left != NULL)
				root->left = insert(root->left, element);
			// Place the node directly to the left of root.
			else
				root->left = element;
		}
	// Return the root pointer of the updated tree.
	return root;
	}
}

struct tree_node* buildTree(FILE* in){
	int n, i, price, count;
	fscanf(in, "%d", &n);
	struct tree_node* temp = NULL;
	struct tree_node* root = NULL;
	
	for (i = 0; i <= n; i++){
		fscanf(in, "%d %d", &price, &count);
		printf("%d %d\n", price, count);
		temp = create_node(price, count);
		root = insert(root, temp);
	}
	return root;
}

void inorder(struct tree_node* root){
	printf("inorder");
	inorder(root->left);
	printf("(%d, %d), ", root->price, root->count);
	inorder(root->right);
}

struct tree_node* create_node(int price, int count) {
	// Allocate space for the node, set the fields.
	struct tree_node* temp;
	temp = (struct tree_node*)malloc(sizeof(struct tree_node));
	temp->price = price;
	temp->count = count;
	temp->left = NULL;
	temp->right = NULL;
	return temp; // Return a pointer to the created node.
}

int totalHouses(struct tree_node* root){
	while (root != NULL){
		return root->count + totalHouses(root->left) + totalHouses(root->right);
	}
	return 0;
}

int totalValue(struct tree_node* root){
	while (root != NULL){
		return (root->price*root->count) + totalValue(root->left) + totalValue(root->right);
	}
	return 0;
}
