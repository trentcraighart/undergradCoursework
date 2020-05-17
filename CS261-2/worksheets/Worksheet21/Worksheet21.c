Worksheet21

int containsDynArr (struct DynArr * da, TYPE e) { 
	int i;
	for(i = 0; i < da->size; i++){
		if(da->data[i] == e){
			return 1;
		}
	}
	return 0;
 
 
 
 
} 
 
        1. What should the removeAt method do if the index given as argument is not in range?  
        	The function should prompt an error and return -1 to indicate an error. 

        2. What is the algorithmic complexity of the method removeAt? Given your answer to the previous question, what is the worst-case complexity of the method remove?  
        	If you are given the first element to remove, your complexity would be O(n)

        3. What are the algorithmic complexities of the operations add and contains?  
        	Add has the complexity of O(1)
        	Contains has the complexity of O(n) due to worst case where it's not in the list. 