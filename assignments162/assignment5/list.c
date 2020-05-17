#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**********
 * Function: init
 * Description: this function sets the head/tail to NULL
 * Parameters: the list as a pointer
 * Pre-Conditions: none
 * Post-Conditions: none
**********/
//***NOTE***
//ONLY CALL WHEN INITIALIZING THE LIST! WILL CAUSE MEMORY LEAKS OTHERWISE!
//**********

void init(struct list* cur_stack){
	cur_stack->head = NULL;
	cur_stack->tail = NULL;
}

/**********
 * Function: push_back
 * Description: thsi function takes an integer and makes a new node for it at the end of the list
 * Parameters: the list as a pointer, the new int
 * Pre-Conditions: none
 * Post-Conditions: none
**********/

void push_back(struct list* cur_stack, int new_int){
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
		new_node->prev = cur_stack->tail;
		cur_stack->tail->next = new_node;
		cur_stack->tail = new_node;
	}
}

/**********
 * Function: push_front
 * Description: this function takes an integer and makes a new node for it at the begining of the list
 * Parameters: the list as a pointer, the new int
 * Pre-Conditions: none
 * Post-Conditions: none
**********/

void push_front(struct list* cur_stack, int new_int){
	struct node* new_node;
	new_node = (struct node*)malloc(sizeof(struct node)*1);
	new_node->val = new_int;
	new_node->next = NULL;
	if(cur_stack->tail == NULL){
		cur_stack->tail = new_node;
	}
	if(cur_stack->head == NULL){
		cur_stack->head = new_node;
	}else{
		new_node->next = cur_stack->head;
		cur_stack->head->prev = new_node;
		cur_stack->head = new_node;
	}
	
}

/**********
 * Function: pop
 * Description: this function will return the last nodes value and remove that node
 * Parameters: the list as a pointer
 * Pre-Conditions:
 * Post-Conditions: will return an integer from the last node
**********/

int pop(struct list* cur_stack){
	if(cur_stack->head == NULL){
		printf("Nothing on stack to pop\n");
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

/**********
 * Function: length
 * Description: this will return the length of the list
 * Parameters: the list
 * Pre-Conditions: none
 * Post-Conditions: will return the length as an int
**********/

int length(struct list cur_stack){
	if(cur_stack.head != NULL){
		struct node* cur_node;
		cur_node = cur_stack.head;
		int cur_num = 1;
		while(cur_node->next != NULL){
			cur_num = cur_num + 1;
			cur_node = cur_node->next;
		}
		return cur_num;
	}else{
		return 0;
	}
}

/**********
 * Function: print
 * Description: will print the contents of the list sequentially
 * Parameters: the list
 * Pre-Conditions: none
 * Post-Conditions: none
**********/

void print(struct list cur_stack){
	if(cur_stack.head != NULL){
		struct node* cur_node;
		cur_node = cur_stack.head;
		int i = 0, num;
		printf("%d is %d\n", i, cur_node->val); 
		while(cur_node->next != NULL){
			cur_node = cur_node->next;
			i = i+1;	
			printf("%d is %d\n", i, cur_node->val); 
		}
	}else{
		printf("There is nothing in this list to print\n");
	}
}

/**********
 * Function: print_row
 * Description: will print the contents of the list horizontally
 * Parameters: the list
 * Pre-Conditions: none
 * Post-Conditions: none
**********/

void print_row(struct list cur_stack){
	if(cur_stack.head != NULL){
		struct node* cur_node;
		cur_node = cur_stack.head;
		int i = 0, num;
		printf("%d  ", cur_node->val); 
		while(cur_node->next != NULL){
			cur_node = cur_node->next;
			i = i+1;	
			printf("%d  ", cur_node->val); 
		}
		printf("\n");
	}else{
		printf("There is nothing in this list to print\n");
	}
}

/**********
 * Function: clear
 * Description: this function will clean all the dynamic memory for the list
 * Parameters: the list as a pointer
 * Pre-Conditions: none
 * Post-Conditions: none
**********/
//***NOTE***
//The list will still exist and still can be used after a clear call
//**********

void clear(struct list* cur_stack){
	if(cur_stack->head != NULL){
		struct node* cur_node;
		cur_node = cur_stack->head;
		while(cur_node != cur_stack->tail){
			cur_node = cur_node->next;
			free(cur_node->prev);
		}
		free(cur_stack->tail);
		cur_stack->head = NULL;
		cur_stack->tail = NULL;
	}
}

/**********
 * Function: remove_val
 * Description: this function will parse the list and remove any node with a certian value
 * Parameters: the list as a pointer, the int that you wish to remove
 * Pre-Conditions: none
 * Post-Conditions: the list will remove the values intended, shortening the list if instances are found
**********/

void remove_val(struct list* cur_stack, int r_val){
	if(cur_stack->head != NULL){
		struct node* cur_node;
		cur_node = cur_stack->head;
		while(cur_node != cur_stack->tail){
			if(cur_node->val == r_val){
				if(cur_node == cur_stack->head){
					cur_stack->head = cur_stack->head->next;
					free(cur_node);
					cur_node = cur_stack->head;
				}else{
					cur_node->prev->next = cur_node->next;
					cur_node->next->prev = cur_node->prev;
					free(cur_node);
					cur_node = cur_stack->head;
				}
			}else{
				cur_node = cur_node->next;
			}
		}
		if(cur_stack->tail->val == r_val){
			if(cur_stack->tail != cur_stack->head){
				cur_node = cur_stack->tail;
				cur_stack->tail = cur_stack->tail->prev;
				cur_stack->tail->next = NULL;
				free(cur_node);
			}else{
				free(cur_stack->tail);	
				cur_stack->head = NULL;
				cur_stack->tail = NULL;
			}
		}
	}
}

/**********
 * Function: insert
 * Description: this will insert a node at a specific part of the list with a specified value
 * Parameters: the list as a pointer, the location as an integer, the value you want the node to contain
 * Pre-Conditions: none
 * Post-Conditions: a new node will be made and added to its spot
**********/

void insert(struct list* cur_stack, int loc, int cur_val){
	int tot, cur_loc = 0, done = 0;
	tot = length(*cur_stack);
	if(tot == 0){
		push_front(cur_stack, cur_val);
	}else{
		if(tot == loc){
			push_back(cur_stack, cur_val);
		}else{
			if(loc <= tot && loc >= 0){
				struct node* cur_node;
				struct node* new_node;
				new_node = (struct node*)malloc(sizeof(struct node)*1);
				new_node->val = cur_val;
				cur_node = cur_stack->head;
				while(done == 0){
					if(cur_loc == loc){
						done = 1;
						if(cur_node->prev != NULL){
							cur_node->prev->next = new_node;
						}else{
							cur_stack->head = new_node;
						}
						new_node->prev = cur_node->prev;
						new_node->next = cur_node;
						cur_node->prev = new_node;
		
					}else{
						cur_loc = cur_loc + 1;
						cur_node = cur_node->next;
					}
				}
			}else{
				printf("Not in range\n");
			}
		}
	}
}

/**********
 * Function: sort_ascending
 * Description: this will reorginize the list's values until it is sorted from smallest to largest
 * Parameters: the list as a pointer
 * Pre-Conditions:
 * Post-Conditions: the list will be reorginized
**********/

void sort_ascending(struct list* cur_stack){
	struct node* cur_node;
	int temp;
	cur_node = cur_stack->head;
	while(cur_node->next != NULL){
		if(cur_node->val > cur_node->next->val){
			temp = cur_node->val;
			cur_node->val = cur_node->next->val;
			cur_node->next->val = temp;
			cur_node = cur_stack->head;

			//HERE IS AN IDEA I HAD FOR EFFICIENCY

/*			while(cur_node->val < cur_node->prev->val){	
				printf("Running sub while loop\n");
				temp = cur_node->val;
				cur_node->val = cur_node->next->val;
				cur_node->next->val = temp;
				cur_node = cur_node->prev;
			}				
*/		
		}else{
			cur_node = cur_node->next;
		}
	}
}

/**********
 * Function: sort_descending
 * Description: this will reorginize the list's values until it is sorted from largest to smallest
 * Parameters: the list as a pointer
 * Pre-Conditions: none 
 * Post-Conditions: the list will be reorginized
**********/

void sort_descending(struct list* cur_stack){
	struct node* cur_node;
	int temp;
	cur_node = cur_stack->head;
	while(cur_node->next != NULL){
		if(cur_node->val < cur_node->next->val){
			temp = cur_node->val;
			cur_node->val = cur_node->next->val;
			cur_node->next->val = temp;
			cur_node = cur_stack->head;
		}else{
			cur_node = cur_node->next;
		}
	}
}
