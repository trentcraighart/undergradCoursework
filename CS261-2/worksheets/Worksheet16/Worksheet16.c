Worksheet 16
Introduction to the Dynamic Array  

struct DynArr { TYPE * data;  int size;  int capacity;  }; 
 
 /* initialize a dynamic array structure with given capacity */ 
 void dynArrayInit (struct DynArr * da, int initialCapacity); 
 
 /* internal method to double the capacity of a dynamic array */ 
 void _dynArraySetCapacity (struct DynArr * da); 
 
 /* release dynamically allocated memory for the dynamic array */ 
 void dynArrayFree (struct DynArr * da); 
 
 /* return number of elements stored in dynamic array */ 
 int dynArraysize (struct DynArr * da); 
 
 /* add a value to the end of a dynamically array */ 
 void dynArrayAdd (struct DynArr * da, TYPE e); 
 
 /* remove the value stored at position in the dynamic array */ 
 void dynArrayRemoveAt (struct DynArr * da, int position); 
 
 /* retrieve element at a given position */ 
 TYPE dynArrayGet (struct DynArr * da, int position); 
 
 /* store element at a given position */ 
 void dynArrayPut (struct DynArr * da, int position, TYPE value); 
 


# define TYPE int 
 
struct DynArr {         
TYPE * data;         
int size;         
int capacity; }; 
 
 
void dynArrayPush (struct DynArr * da, TYPE e) {   
	if(da->size == da->capacity){
		_dynArraySetCapacity(da);
	}
	da->data[size] = e;
	da->size++;
} 
 
TYPE dynArrayTop (struct DynArr * da) { 
 	
 	return da->data[size-1];
} 
 
void dynArrayPop (struct DynArr * da) { 
	if(da->size > 0){
		da->size--;
	}
} 
 
int dynArrayIsEmpty (struct DynArr * da) { 

	if(da->size == 0){
		return 1;
	} 
 	return 0;
}

1. What is the algorithmic execution time for the operations pop and top? 
	Pop and top will both have an execution time of O(1)

2. What is the algorithmic execution time for the operation push, assuming there is sufficient capacity for the new elements? 
	Push would take O(1) assuming it doensn't have to resize.
 
3. What is the algorithmic execution time for the internal method _dynArraySetCapacity? 
	O(n) for preforming the operation on each element.

4. Using as a basis your answer to 3, what is the algorithmic execution time for the operation push assuming that a new array must be created. 
	The execution time would be O(n+1) or O(n) due to the resize needing to operate on each element
