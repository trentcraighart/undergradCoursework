# ifndef TYPE # define TYPE int # endif 
 
struct DynArr {  
	TYPE *data; /* pointer to the data array */  
	int size;  /* Number of elements in the array */  
	int capacity; /* capacity of the array */ 
}; 
 
void initDynArr(struct DynArr *v, int capacity) {  
	v->data = malloc(sizeof(TYPE) * capacity);  
	assert(v->data != 0);    
	v->size = 0;  
	v->capacity = capacity; 
}

void freeDynArr(struct DynArr *v) {  
	if(v->data != 0)  {   
		free(v->data);  
		/* free the space on the heap */   
		v->data = 0;    
		/* make it point to null */  
	}  
	v->size = 0;  
	v->capacity = 0; 
} 
 
 
 
int sizeDynArr( struct DynArr *v) {  
	return v->size; 
} 

void   addDynArr(struct DynArr *v, TYPE val) {  
/* Check to see if a resize is necessary */  
	if(v->size >= v->capacity)   
		_setCapacityDynArr(v, 2 * v->capacity);    
	v->data[v->size] = val;  v->size++;  
} 


void _setCapacityDynArr(struct DynArr *v, int newCap) {
	DynArr *newArr;
	newArr = malloc(sizeof(DynArr));
	initDynArr(newArr, newCap);
	int i;
	i = 0;
	//Copy elements over while we can
	while(i < newCap && i < v->size){
		newArr->data[i] = v->data[i];
		i++;
	}
	freeDynArr(v);
	&v = new


}

TYPE getDynArr (struct DynArr * da, int position) { 
	if(da->size > position){
		return da->data[position];
	}else{
		return NULL;
	}
}

void putDynArr(struct DynArr * da, int position, TYPEvalue) { 
	if(da->capacity > position){
		da->data[position] = value;
	}
}


void swapDynArr (struct DynArr * da, int i, int j) { 
	if(da->size > i && da->size > j){
		TYPE temp;
		temp = da->data[i];
		da->data[i] = da->data[j];
		da->data[j] = temp;
	}
}

void removeAtDynArr (struct DynArr * da, int index) { 
	int i;
	i = index;
	//We can ignore the last index because size will keep us from accessing it
	if(index < v->size){
		while(i < v->size - 1){
			v->data[i] = v->data[i+1];
			i++;
		}
	}
	v->size--;

}