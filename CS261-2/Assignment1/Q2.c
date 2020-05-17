/* CS261- Assignment 1 - Q.2*/
/* Name: Trent Vasquez
 * Date: 7/3
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    printf("Value of address a preswap == %p\n", a);
    printf("Value of address b preswap == %p\n", b);
    int* temp;
    temp = b;
    b = a;
    a = temp;
    printf("Value of address a postswap == %p\n", a);
    printf("Value of address b postswap == %p\n", b);
    /*Decrement the value of integer variable c*/
    c--;

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    srand(time(NULL));
    int x, y, z;
    x = rand() % 11;    
    y = rand() % 11; 
    z = rand() % 11;     

    /*Print the values of x, y and z*/

    printf("Value of x == %d\n", x);    
    printf("Value of y == %d\n", y);    
    printf("Value of z == %d\n", z);            

    /*Call foo() appropriately, passing x,y,z as parameters*/
    int output;
    output = foo(&x, &y, z);

    /*Print the values of x, y and z*/
    printf("Value of x == %d\n", x);    
    printf("Value of y == %d\n", y);    
    printf("Value of z == %d\n", z);               

    /*Print the value returned by foo*/
 
    printf("Value of output == %d\n", output);
    
    return 0;
}

/* 
	Question Responses:
	a. Is the return value different than the value of integer z? Why or why not? 
	   The values are different because the scope that we changed c in is just a copy of our z variable

	b. Are the values of integers x and y different before and after calling the function foo(..)? Why or why not?
	   The values of our x and y variables weren't swapped because we the scope we swaped the pointers in were just copies.
*/
    


