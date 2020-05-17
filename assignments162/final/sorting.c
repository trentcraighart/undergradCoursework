#include <stdio.h>
#include <stdlib.h>

typedef struct timeval time;
void print_array(int *, int);
void merge(int *, int, int, int);
void merge_sort(int *, int, int);
void selection_sort(int *, int);
void insertion_sort(int *, int);
void bubble_sort(int *, int);
void fill_array(int **, int *);
void add_num(int **, int *, int);

int main(){
   int *nums=NULL;
   int size=0;
   time stop, start;

   fill_array(&nums, &size);
   print_array(nums, size);

   //Time the function here
   gettimeofday(&start, NULL);
   
   bubble_sort(nums, size);
   //insertion_sort(nums, size);
   //merge_sort(nums, 0, size-1);
   //selection_sort(nums, size);

   gettimeofday(&stop, NULL);

   printf("MicroSeconds: %d\n", stop.tv_usec-start.tv_usec);
   //printf("Seconds: %d\n", stop.tv_sec-start.tv_sec);

   //print_array(nums, size);
   free(nums);

   return 0;
}

/*************************************************
 * Description: This prints the contents of an array
 * Params: array of integers and size of the array
 * Returns: none
 * Post-conditions: none
 * Pre-conditions: size is accurate number of 
 *                 elements in the array >=0
 * **********************************************/
void print_array(int *nums, int size){
   int i;

   printf("The array elements are:\n");
   for(i=0; i<size; i++)
      printf("%d\t", nums[i]);
   printf("\n\n");
}

/*************************************************
 * Description: merge is a sub function of merge_sort that will be called to merge small sets of data
 * Params: array of integers, the leftmost number, the middle of the set, and the furthest right number (typically the beginning, middle, and end)
 * Returns: none
 * Post-conditions: none
 * Pre-conditions: the left, mid, and right values are inside the array
 * ***********************************************/
void merge(int *nums, int left, int mid, int right){
   int i, j, lower_half, upper_half;
   int temp[(right-left)+1];

   lower_half=left;  //What is this for?   Both of these variables are for keeping track of the algorithms current spot in its sort.
   upper_half=mid+1;  //What is this for?  The left starts on at the beginig of the array where mid+1 starts at the begining of the second half of the array.

   
   //What does this loop do?    This loop is checking if the function has sorted all the information yet on both sides. It will know its serched all the values when the lower_half >= mid (it has itterated up enough to reach it)
   //In addition the same holds true for the uper_half, it will know tis done when it hits the >= the right
   //In addition the i holds the location of the current spot in the temperary array

   for(i=0; (lower_half<=mid)&&(upper_half<=right); i++){
      //What does this condition do?         This block is checking if the lower half has the smaller value, if it does it is going to put into the next slot on our temporary array then increment.
      if(nums[lower_half]<=nums[upper_half]){
	 temp[i]=nums[lower_half];
	 lower_half++;
      }
      //What does this condition do?         if the lower half variable is larger, we are going to put the upper half integer onto our temporary array then increment. 
      else{
	 temp[i]=nums[upper_half];
	 upper_half++;
      }
   }

   //What does this condition and loop do?   if the lower half placement went over the the mid marker, the function will take the remaining values from the upper half and place them into the temp array
   if(lower_half>mid)
      for(j=upper_half;j<=right;j++, i++)
	 temp[i]=nums[j];
   //What does this else and loop do?        if the lower half placement DIDN'T go over the mid marker, the function will take the remaining lower half functions and put them onto the array
   else
      for(j=lower_half;j<=mid;j++, i++)
	 temp[i]=nums[j];

   //What does this loop do?                 This loop is strictly copying all the values from the temporary array into the primary array
   for(j=0,i=left;i<=right;i++,j++)
      nums[i]=temp[j];
}

/*************************************************
 * Description: merge_sort will recursivly call itself in order to merge smaller and smaller sets of data (a good way to think is the data is being sifted into smaller sets until it falls into place)
 * Params: array of integers, the leftmost number, the middle of the set, and the furthest right number (typically the begining, middle, and end)
 * Returns: none
 * Post-conditions: none
 * Pre-conditions: the left and right values are acurate
 * ***********************************************/
void merge_sort(int *nums, int left, int right) {
   int mid; 
   if(left<right) {
      mid=(right+left)/2;
      merge_sort(nums, left, mid);  //what does this call do?
      merge_sort(nums, mid+1, right); //what does this call do?
      merge(nums, left, mid, right);  //what does this call do?
   }
}

/*************************************************
 * Description: selection_sort goes though the list each number at a time and checks if there is a number later on that is smaller than it, if there is, they swap locations
 * Params: array of integers as well as its size
 * Returns: none
 * Post-conditions: none
 * Pre-contitions: the size is correct 
 * ***********************************************/
void selection_sort(int *nums, int size) {
   int i, j;
   int temp, min;

   //What does this loop do?              This loop is going though all of the elements in the array
   for(i=0; i<size-1; i++) {
      min=i;
      //What does this loop do?           This loop is is taking the current element, then checking if there the list for a smaller element to swap with it
      for(j=i; j<size; j++)
	 if(nums[j]<nums[min]) 
	    min=j;
      //What elements are being swaped?   This portion of the code is taking the smallest number we found in the second loop and swaping their locations
      temp=nums[i];
      nums[i]=nums[min];
      nums[min]=temp;
   }
}

/*************************************************
 * Description: insertion_sort goes through the list of arrays if it finds a location to place the value, then it values proceeding it down to the right one, and finally place it in the open slot
 * Params: array of integers as well as its size
 * Returns: none
 * Post-conditions: none
 * Pre-contitions: the size is correct
 * ***********************************************/
void insertion_sort(int *nums, int size) {
   int i, j;
   int temp;

   //What does this loop do?           This loop will iterate through all the numbers in the array
   for(i=0; i<size; i++) {
      temp=nums[i]; 
      //What does this loop do?        This loop is checking for an apropriate spot to place the new value, if it findes one, it will insert it, then move all the others down
      for(j=i; j>0 && nums[j-1]>temp; j--) 
	 nums[j]=nums[j-1];
      //What does this statment do?    This statement is placing the temp value in the slot it just opend by pushing the other numbers down
      nums[j]=temp; 
   }
}

/*************************************************
 * Description: bubble_sort will take a value and compare it to all the values that proceed it in the array and "bubble" it down the list until it finds the right spot
 * Params: an array of integers as well as the size
 * Returns: none
 * Post-conditions: none
 * Pre-contitions: the size needs to be correct
 * ***********************************************/
void bubble_sort(int *nums, int size) {
   int i, j;
   int temp;

   //What does this loop do?         This loop iterates through the size of the array
   for(i=0; i<size; i++) {
      //What does this loop do?      This loop checks if the current number is greater then the number that proceeds it, if it does, it swaps places. This for loop will check values all down the list
      for(j=0; j<size-i-1; j++) {
	 if(nums[j]>nums[j+1]) {
	    temp=nums[j];
	    nums[j]=nums[j+1];
	    nums[j+1]=temp;
	 }
      }
   }
}

/*************************************************
 * Description: This adds an element to the array
 * and sets the contents to num
 * Params: address of array pointer to ints and 
 *         address of size of the array
 * Returns: none
 * Post-conditions: size is increased by one and
 * nums points to new array with one more element
 * where the contents are the same with num at the end
 * Pre-conditions: nums points to valid array or NULL
 * and size is accurate number of elements in array >=0
 * **********************************************/
void add_num(int **nums, int *size, int num){
   int *old_nums, i;

   *size+=1;
   old_nums=*nums;
   *nums=(int *) malloc(sizeof(int)*(*size));

   for(i=0; i<*size-1; i++)
      (*nums)[i]=old_nums[i];
   (*nums)[*size-1]=num;

   free(old_nums);
}

/*************************************************
 * Description: This fills an array with contents
 * from a file
 * Params: address of array pointer to ints and 
 *         address of size of the array
 * Returns: none
 * Post-conditions: array pointer is pointing to
 * valid array of integers or NULL and size has
 * a positive integer
 * Pre-conditions: nums points to valid array or NULL
 * and size is accurate number of elements in array >=0
 * **********************************************/
void fill_array(int **nums, int *size) {
   FILE *fptr;
   char filename[20], num[10];

   printf("Enter the filename: ");
   scanf("%s",filename);
   fptr=fopen(filename,"r");

   while(fscanf(fptr,"%s", num)!=EOF){
      add_num(nums, size, atoi(num));
   }

   fclose(fptr);
}
