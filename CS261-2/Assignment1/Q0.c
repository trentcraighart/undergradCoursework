/* CS261- Assignment 1 - Q. 0*/
/* Name: Trent Vasquez
 * Date: 7/3
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){
  
     /*Print the value and address of the integer pointed to by iptr*/
    printf("What iptr is looking at == %p\n", iptr);
    printf("Value of what iptr is looking at == %d\n", *iptr);
     /*Increment the value of the integer pointed to by iptr by 5*/
          
    *iptr = *iptr + 5;
     /*Print the address of iptr itself*/

    printf("Address of iptr == %p\n", &iptr); 

    /*Dummy variable, ignore the warning*/
    int c=5;  
}


void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/
    printf("What jptr is looking at == %p\n", jptr);
    printf("Value of what jptr is looking at == %d\n", *jptr);        

     /*Decrement the address by 1 pointed to by jptr using jptr */
    jptr--;
      
     /*Print the address of jptr itself*/
    printf("Address of jptr == %p\n", &jptr);
}


int main(){
    
    /*Declare an integer x and initialize it randomly to a value in [0,10] 
*/
    srand(time(NULL));
    int x;
    x = rand() % 11;

    /*Print the value and address of x*/
    printf("Address of x == %p\n", &x);    

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*Print the value of x*/
    printf("Value of x == %d\n", x);    

    /*Call fooB() with the address of x*/
    fooB(&x);

    /*Print the value and address of x*/
    printf("New value of x == %d\n", x);        
    printf("New address of x == %p\n", &x);  
    
    return 0;
}

/*
    Question Responses:
    Are the value and address of x different than the value and address that were printed before the call to fooB(..)? Why or why not? 
    They values didn't change because when we were working the scope of fooB, it wasn't changing what was happening in main. 
*/
