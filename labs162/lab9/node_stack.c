#include <stdio.h>
#include <stdlib.h>

struct node{
	int val;
	struct node *next;
};

struct stack{
	struct node *head;
	struct node *tail;
};

void init(struct stack* new_stack){
	printf("In the function init\n");	

	new_stack->head = (struct node*)malloc(sizeof(struct node)*1);
	//new_stack->tail = (struct node*)malloc(sizeof(struct node)*1);
	printf("Passed first allocate\n");	
	new_stack->head->next = NULL;
	new_stack->head = new_stack->tail;
	printf("End of function\n");
}

void push(struct stack* cur_stack, int new_num){
	struct node* temp;
	temp->val = new_num;
	temp = (struct node*) malloc(sizeof(struct node)*1);
	printf("Made it past alloc\n");
	cur_stack->tail->next = temp;
	cur_stack->tail->next = (struct node*) malloc(sizeof(struct node)*1);
	printf("set the next of tail\n");
	cur_stack->tail = temp;
	printf("set tail\n");
	if(cur_stack->head == NULL){
		cur_stack->head = cur_stack->tail;
	}
	printf("through function\n");



	/*struct node temp;
	struct node* adr_temp;
	adr_temp = &temp;
	adr_temp = (struct node*)malloc(sizeof(struct node)*1);*/
	/*
	printf("at the begining\n");	
	cur_stack->tail->next = (struct node*)malloc(sizeof(struct node)*1);
	printf("cur_stack->tail->next = (struct node*)malloc(sizeof(struct node)*1);\n");
	cur_stack->tail = cur_stack->tail->next;
	printf("cur_stack->tail = cur_stack->tail->next;\n");
	cur_stack->tail->val = new_num;
	printf("cur_stack->tail->val = new_num;\n");
	cur_stack->tail->next = NULL;
	printf("cur_stack->tail->next = NULL;\n"); */
}

int pop(struct stack* cur_stack){
	int ret_num;
	struct node* temp;
	if(cur_stack->head == NULL){
		printf("Nothing to pop");
	}else{
		int i = 1;
		temp->next = cur_stack->head->next;
		while(temp->next != NULL){
			i++;
			temp->next = temp->next->next;
		}
		ret_num = temp->val;
		free(temp);
		temp->next = cur_stack->head->next;
		for(i ;i>2 ;i--){	
			temp->next = temp->next->next;
		}
		temp->next = NULL;
	}
}

int main(){
	struct stack run_stack;
	printf("Made stack\n");
	init(&run_stack);

	push(&run_stack, 1);
	push(&run_stack, 2);
	push(&run_stack, 3);
	push(&run_stack, 4);
	
	printf("pushed 4 values");

	int i;
	i = pop(&run_stack);
	printf("Poped off %d", i);
	i = pop(&run_stack);
	printf("Poped off %d", i);
	i = pop(&run_stack);
	printf("Poped off %d", i);
	i = pop(&run_stack);
	printf("Poped off %d", i);
	i = pop(&run_stack);
	printf("Poped off %d", i);

	return 0;
}
