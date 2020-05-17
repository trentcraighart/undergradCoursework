/**********
 * Program: test_list.c
 * Author: Trent Vasquez
 * Date: 6/4/2016
 * Description: This program was made to show minipulation of linked lists in several ways
**********/

//***NOTE***
//The random.cpp program was made to generate random lists to help test this program
//**********

#include "list.c"
#include <stdio.h>
#include <stdlib.h>

int main(){
	char filename[20];
	struct list l;
	FILE *fileptr;
	char num[3];
	int len;

	printf("Enter filename: ");
	scanf("%s", filename);
	fileptr = fopen(filename, "r");

	while(fscanf(fileptr, "%s", num)!=EOF){
		printf("number is: %d\n", atoi(num));
		push_front(&l, atoi(num));	
		push_back(&l, atoi(num));	
	}
	
	len = length(l);
	printf("Length is %d\n", len);
	print(l);

	printf("In Ascending Order\n");
	sort_ascending(&l);
	print(l);

	printf("In Descending Order\n");
	sort_descending(&l);
	print(l);

	int rem;
	printf("Enter a number you wish to remove from the list: ");
	scanf("%d", &rem);
	remove_val(&l, rem);

	print(l);

	int add, spot;
	printf("Enter a number you wish to add to the list: ");
	scanf("%d", &add);
	printf("Enter the location you wish to place it: ");
	scanf("%d", &spot);
	insert(&l, spot, add);
	
	print(l);

	clear(&l);

	fclose(fileptr);
		
	return 0;
}

	
