#include <stdio.h>
#include <stdlib.h>

struct stack{
	int *contents; //dynamic array of ints
	int top; //stores the top of the stack
	int ele; //number of elements in array
};

void init(struct stack* new_stack){
	new_stack->contents = (int *) malloc(sizeof(int)*0);
	new_stack->ele = 0;
	
}

void push(struct stack* the_stack, int new_num){
	struct stack temp_stack;
	int i;
	temp_stack.contents = (int *) malloc(sizeof(int)*the_stack->ele);
	for(i = 0; i < the_stack->ele; i++){
		temp_stack.contents[i] = the_stack->contents[i];
	}
	free(the_stack->contents);
	the_stack->ele = the_stack->ele + 1;
	the_stack->contents = (int *) malloc(sizeof(int)*the_stack->ele);
	for(i = 0; i < the_stack->ele; i++){
		the_stack->contents[i] = temp_stack.contents[i];
	}
	free(temp_stack.contents);
	the_stack->contents[the_stack->ele - 1] = new_num;
}

int pop(struct stack* cur_stack){
	if(cur_stack->ele > 0){
		struct stack temp_stack;
		int i, last_num;
		last_num = cur_stack->contents[cur_stack->ele - 1];
		printf("Last number in pop is: %d \n", last_num);
		temp_stack.contents = (int *) malloc(sizeof(int)*cur_stack->ele);
		for(i = 0; i < cur_stack->ele; i++){
			temp_stack.contents[i] = cur_stack->contents[i];
		}
		free(cur_stack->contents);
		cur_stack->ele = cur_stack->ele - 1;
		cur_stack->contents = (int *) malloc(sizeof(int)*cur_stack->ele);
		for(i = 0; i < cur_stack->ele; i++){
			cur_stack->contents[i] = temp_stack.contents[i];
		}
		free(temp_stack.contents);
		return last_num;
	}else{
		printf("There is nothing on your stack");
		return 0;
	}	
}

int peek(struct stack cur_stack){
	return cur_stack.contents[cur_stack.ele - 1];
}

void destroy(struct stack* cur_stack){
	free(cur_stack->contents);
	cur_stack->ele = 0;
	printf("The contents of the stack have been destroyed\n");
}

// True = 1 False = 0
int empty(struct stack cur_stack){
	if(cur_stack.ele > 0){
		return 0;
	}else{
		return 1;
	}
}

int size(struct stack cur_stack){
	return cur_stack.ele;
}

int main(){
	int num;
	struct stack new_stack;
	init(&new_stack);
	printf("Going to push 1, 2, 3 on the stack\n");
	push(&new_stack, 1);
	push(&new_stack, 2);
	push(&new_stack, 3);
	num = pop(&new_stack);
	printf("Num at the end is %d \n", num);
	num = pop(&new_stack);
	printf("Num at the end is %d \n", num);
	printf("Only going to peek at next num\n");
	num = peek(new_stack);
	printf("Num at the end is %d \n", num);
	printf("Going to check if 0\n");
	num = empty(new_stack);
	printf("Is empty = %d \n", num);
	printf("Is about to destroy\n");
	destroy(&new_stack);	
	printf("Going to check if 0\n");
	num = empty(new_stack);
	printf("Is empty = %d \n", num);
	printf("Going to push 1, 2, 3 on the stack\n");
	push(&new_stack, 1);
	push(&new_stack, 2);
	push(&new_stack, 3);
	printf("Checking num of elements\n");
	num = size(new_stack);
	printf("Num of elements is %d \n", num);
	
	destroy(&new_stack);


}
