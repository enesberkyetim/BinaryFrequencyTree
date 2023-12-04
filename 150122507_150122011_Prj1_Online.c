// Melisa Araç - 150122011 / Enes Berk Yetim - 150122507

#include <stdio.h>
#include <stdlib.h>


struct node{
	int number;
	int frequency;
	struct node * leftPtr;
	struct node * rightPtr;
	
	
};

void comparison (struct node* old_node,struct node* new_node){
	if((old_node->number<new_node->number)){
		if(old_node->rightPtr==NULL){
		old_node->rightPtr=new_node;	
		}
		else{
		comparison(old_node->rightPtr,new_node);	
		}
		}
	else if(old_node->number>new_node->number){
		if(old_node->leftPtr==NULL){
		old_node->leftPtr=new_node;	
		}
		else{
		comparison(old_node->leftPtr,new_node);	
		}
		
	}
	
}

struct node* comparison_offline(struct node* old_node, struct node* new_node){
	if((old_node->number<new_node->number)){
		if((old_node->rightPtr==NULL) && (old_node->frequency>=new_node->frequency)){
			old_node->rightPtr=new_node;	
		}
		else if ((old_node->frequency<new_node->frequency)){
			struct node* temp = malloc(sizeof(struct node));
			*temp = *old_node;
			*old_node = *new_node;
			old_node->leftPtr = temp;
		}
		else {
			comparison_offline(old_node->rightPtr,new_node);	
		}
	}
	else if((old_node->number>new_node->number)){
		if((old_node->leftPtr==NULL) && (old_node->frequency>=new_node->frequency)){
			old_node->leftPtr=new_node;	
		}
		else if ((old_node->frequency<new_node->frequency)){
			struct node* temp = malloc(sizeof(struct node));
			*temp = *old_node;
			*old_node = *new_node;
			old_node->rightPtr = temp;
		}
		else {
			comparison_offline(old_node->leftPtr,new_node);	
		}
		
	}
	return old_node;
}

struct node* comparison_online(struct node* root){
	struct node* left = root->leftPtr;
	struct node* right = root->rightPtr;
	
	if (left != NULL) {
		if (left->frequency > root->frequency) {
			struct node* temp_root = malloc(sizeof(struct node));
			struct node* temp_right = malloc(sizeof(struct node));
		
			*temp_root = *root;
			temp_root->leftPtr = NULL;
			
			if (root->leftPtr->rightPtr != NULL) {
				*temp_right = *(root->leftPtr->rightPtr);
			}
			else {
				free(temp_right);
				temp_right = NULL;
			}
			
		
			*root = *(root->leftPtr);
			root->rightPtr = temp_root;
			
			if (temp_right != NULL) {
				root->rightPtr->leftPtr = temp_right;
			}
			
		}
		else {
			comparison_online(left);
		}	
	}

	if (right != NULL) {
		if (right->frequency > root->frequency) {
			struct node* temp_root = malloc(sizeof(struct node));
			struct node* temp_left = malloc(sizeof(struct node));
		
			*temp_root = *root;
			temp_root->rightPtr = NULL;
			
			if (root->rightPtr->leftPtr != NULL) {
				*temp_left = *(root->rightPtr->leftPtr);
			}
			else {
				free(temp_left);
				temp_left = NULL;
			}
			
		
			*root = *(root->rightPtr);
			root->leftPtr = temp_root;
			
			if (temp_left != NULL) {
				root->leftPtr->rightPtr = temp_left;
			}
			
		}
		else {
			comparison_online(right);
		}
	}
	
	
	return root;
}

void find(struct node* root, int search){
	if (root != NULL) {
		if (root->number<search){
			find(root->rightPtr, search);
		}
		else if (root->number>search){
			find(root->leftPtr, search);
		}
		else if (root->number==search){
			root->frequency=root->frequency + 1;
		}
	}
	
}

void preorder(struct node* root){
		
	if(root != NULL){
	printf("(%d, %d) ",root->number, root->frequency);
	preorder(root->leftPtr);
	preorder(root->rightPtr);
}

}

int main(int argc, char *argv[]){
	FILE *input_file;
	struct node* root;
	int count = 0;
	
	if (fopen(argv[1], "r") == NULL) {
		printf("File not exist");
	}
	else {
		input_file = fopen(argv[1], "r");
		
		struct node* node;
		struct node* root;
		while(!feof(input_file)) {
			int number;
			int frequency;
			fscanf(input_file, "%d", &number);
			struct node* nodePtr = malloc(sizeof(struct node));
			nodePtr->number = number;
			nodePtr->frequency = 0;
			nodePtr->leftPtr = NULL;
			nodePtr->rightPtr = NULL;
			
			
			if (count==0) {
			node=nodePtr;
			}
			else {
			root = comparison_offline(node, nodePtr);
			}	
			count++;
		}
		
		printf("\n\n");
		printf("Preorder traversal of the constructed tree : ");
		preorder(root);
		printf("\n");
		
		while(1) {
			int search = 0;
			
			printf("Enter a value to search : ");
			scanf("%d", &search);
			printf("\n");
			
			find(root, search);
			root = comparison_online(root);
			
			printf("Preorder traversal of the constructed tree : ");
			preorder(root);
			
			printf("\n");
		}
		
	}
}
//15 8 7 16 9 5 19 12


