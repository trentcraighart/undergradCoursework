
/* Bag Implementation */ 
void initBag (struct arrayBagStack * b){ 
 
 /* Insert your code */  
 /* You have to initialize the count variable to 0 only */ 
 	b->count = 0;

}  

void addBag (struct arrayBagStack * b, TYPE v) { 
 
 /* Insert your code */ 
 /* add the value to the end of the array */ 
	if(b->count != 100){
		b->data[b->count] = v;
		b->count++;
 	}else{
 		printf("Bag is full, item v couldn't be added\n");
 	}
} 
 
int containsBag (struct arrayBagStack * b, TYPE v) { 
 
 /* Insert your code */ 
	int i;
	i = 0;
	while(i < b->count){
		if(b->data[i] == v){
			//Found item
			return 1;
		}
		i++;
	}
	return 0;
} 
 
void removeBag (struct arrayBagStack * b, TYPE v) { 
 
 /* Insert your code */ 
	if(containsBag(b, v) == 0){
		return -1;
	}
	int i, del;
	i = 0; del = 0;
	while(i < b->count){
		if(del == 0){
			if(v == b->data[i]){
				del++;
			}
			i++;
		}else{
			b->data[i - 1] = b->data[i]; 
		}
	}

}  
 
int sizeBag (struct arrayBagStack * b) { 
 
 /* Insert your code */ 
	return b->count;
}  
 
 
/* Stack Implementation */ 
void pushStack (struct arrayBagStack * b, TYPE v) { 
 
 /* Insert your code */ 
	if(b->count != 100){
		b->data[b->count] = v;
		b->count++;
 	}else{
 		printf("Bag is full, item v couldn't be added\n");
 	} 


} TYPE topStack (struct arrayBagStack * b) { 
 
 /* Insert your code */ 
	if(b->count == 0){
		printf("Nothing in the bag");
		return NULL;
	}
	return(b->data[b->count - 1]);

}  
 
void popStack (struct arrayBagStack * b) { 

 /* Insert your code */ 
	if(b->count != 0){
		b->count--;
	}

}   

 int isEmptyStack (struct arrayBagStack * b) { 
 /* Insert your code */ 
 	if(b->count == 0){
 		return 1;
 	}
 	return 0;

}  

