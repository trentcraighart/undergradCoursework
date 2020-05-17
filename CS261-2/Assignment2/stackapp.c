/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre:	Takes a null terminated string or NULL input 	
	post:	Returns 0 if balanced, 1 if unbalanced
	post:	Returns 0 if Null input
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */		
	DynArr *stack;
	stack = newDynArr(2);
	if(s == NULL){
		return 1;
	}
	char tmp;
	tmp = nextChar(s);
	while(tmp != '\0'){
		if(tmp == '(' || tmp == '[' || tmp == '{'){
			pushDynArr(stack, tmp);
		}
		if(tmp == ')'){
			if(topDynArr(stack) == '('){
				popDynArr(stack);
			}else{
				return 0;
			}
		}
		if(tmp == '}'){
			if(topDynArr(stack) == '{'){
				popDynArr(stack);
			}else{
				return 0;
			}
		}
		if(tmp == ']'){
			if(topDynArr(stack) == '['){
				popDynArr(stack);
			}else{
				return 0;
			}
		}				
		tmp = nextChar(s);
	}
	if(isEmptyDynArr(stack)){
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

