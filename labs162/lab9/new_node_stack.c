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

void init(struct stack* cur_stack){
	cur_stack->head = NULL;
	cur_stack->tail = NULL;
}

void push(struct stack* cur_stack, int new_int){
	struct node* new_node;
	new_node = (struct node*)malloc(sizeof(struct node)*1);
	new_node->val = new_int;
	new_node->next = NULL;
	if(cur_stack->head == NULL){
		cur_stack->head = new_node;
	}
	if(cur_stack->tail == NULL){
		cur_stack->tail = new_node;
	}else{
		cur_stack->tail->next = new_node;
		cur_stack->tail = new_node;
	}
}

int pop(struct stack* cur_stack){
	if(cur_stack->head == NULL){
		printf("Nothing on stack to pop ");
		return 0;
	}else{
		int i = 1, j, d = 0, v; //i is increment, j is increment, d is done, v is return
		struct node* cur_node;
		if(cur_stack->head->next == NULL){
			v = cur_stack->head->val;
			free(cur_stack->head);
			cur_stack->head = NULL;
			return v;
		}else{
			cur_node = cur_stack->head;
			while(cur_node->next->next != NULL){
				cur_node = cur_node->next;
			}
			v = cur_node->next->val;
			free(cur_node->next);
			cur_node->next = NULL;
			cur_stack->tail = cur_node;
			return v;	
		}
	}
}


int main(){
	struct stack new_stack;
	int i, v;
	init(&new_stack);
	for(i = 0; i < 8; i++){
		printf("About to push %d\n", i);
		push(&new_stack, i);
	}
	for(i = 0; i < 5; i++){
		v = pop(&new_stack);
		printf("Popped off %d\n", v);
	}
	for(i = 0; i < 9; i++){
		printf("About to push %d\n", i);
		push(&new_stack, i);
	}
	for(i = 0; i < 20; i++){
		v = pop(&new_stack);
		printf("Popped off %d\n", v);
	}
}

