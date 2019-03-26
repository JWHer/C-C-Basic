#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char data;
	struct node *left;
	struct node *right;
}node;

node* CreateNode(char newdata) {
	node* NewNode = (node*)malloc(sizeof(node));
	NewNode->left = NULL;
	NewNode->right = NULL;
	NewNode->data = newdata;
	return NewNode;
}

void preorderPrintTree(node* root) {
	if (root == NULL) return;
	printf("%c ", root->data);
	preorderPrintTree(root->left);
	preorderPrintTree(root->right);
}
void inorderPrintTree(node* root) {
	if (root == NULL) return;
	inorderPrintTree(root->left);
	printf("%c ", root->data);
	inorderPrintTree(root->right);
}
void postorderPrintTree(node* root) {
	if (root == NULL) return;
	postorderPrintTree(root->left);
	postorderPrintTree(root->right);
	printf("%c ", root->data);
}
void setNode(node *root, int n) {
	if (root == NULL) return;
	root->left = CreateNode(2*n+96);
	root->right = CreateNode(2*n+97);
}
int main() {
	node *root = CreateNode('a');
	node *p = root;
	setNode(p, 1);
	p = root->left;
	setNode(p, 2);
	p = root->right;
	setNode(p, 3);

	preorderPrintTree(root);
	printf("\n");
	inorderPrintTree(root);
	printf("\n");
	postorderPrintTree(root);
	printf("\n");
}