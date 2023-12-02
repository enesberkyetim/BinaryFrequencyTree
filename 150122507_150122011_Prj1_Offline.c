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
		if((old_node->rightPtr==NULL) && (old_node->frequency>new_node->frequency)){
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
		if((old_node->leftPtr==NULL) && (old_node->frequency>new_node->frequency)){
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


void preorder(struct node* root){
		
	if(root != NULL){
	printf("%d ",root->number);
	preorder(root->leftPtr);
	preorder(root->rightPtr);
}

}

int main(int argc, char *argv[]){
	FILE *input_file;
	struct node* root;
	
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
			fscanf(input_file, "%d, %d", &number, &frequency);
			struct node* nodePtr = malloc(sizeof(struct node));
			nodePtr->number = number;
			nodePtr->frequency = frequency;
			nodePtr->leftPtr = NULL;
			nodePtr->rightPtr = NULL;
			
			
			if (count==0) {
			node=nodePtr;
			}
			else {
			root = comparison_offline(node,nodePtr);
			}
			count++;
		}
		
		printf("\n\n");
		preorder(root);
		
	}
}
//15 8 7 16 9 5 19 12


