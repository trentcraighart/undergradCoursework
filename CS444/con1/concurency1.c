#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "twister.h"
#include <time.h>
#include <x86intrin.h>

/*Structs*/
struct dualNumbers{
	int randomInteger;
	int randomWait;
};

/*Functions*/
void* producerFunction(void*);
void* consumerFunction(void*);
unsigned int GetRandomViaRDRAND();

/*Globals*/
int globalNumber;
int currentPointer;
int randFunction;
struct dualNumbers buffer[32];
pthread_t tid[2];
pthread_mutex_t lock;



int main(int argc, char **argv)
{
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;


	char vendor[13];
	
	eax = 0x01;

	__asm__ __volatile__(
	                     "cpuid;"
	                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	                     : "a"(eax)
	                     );
	
	if(ecx & 0x40000000){
		//use rdrand
		printf("using rrand\n");
		randFunction = 1;
	}
	else{
		//use mt19937
		init_genrand((unsigned long)time(NULL));		
		printf("using mt19937\n");
		randFunction = 2;
	}

	//fill buffer
	int i;
	for(i = 0; i < 32; i++){
		buffer[i].randomInteger = 0;
		buffer[i].randomWait = 0;
	}

	//Here we are going to create the two threads and mutex lock

	//currentPointer = 0;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&(tid[0]), NULL, &producerFunction, NULL);
	pthread_create(&(tid[1]), NULL, &consumerFunction, NULL);


	while(1){
		randFunction = randFunction;
	}

	return 0;
}

//NOTE, for simplicity I will be having the buffer like a stack
//      currentElement being a pointer to the current value

void* producerFunction(void *args){
	int waitTime;
	struct dualNumbers currentElement;
	while(1){	
		if(randFunction == 2){
			currentElement.randomWait = (genrand_int32() % 8 + 2);
			currentElement.randomInteger = (genrand_int32() % 1000);
			waitTime = (genrand_int32() % 7 + 3);
		}else{
			currentElement.randomWait = (GetRandomViaRDRAND() % 8 + 2); 
			currentElement.randomInteger = (GetRandomViaRDRAND() % 1000); 
			waitTime = (GetRandomViaRDRAND() % 7 + 3);
		}	

		sleep(waitTime);
		while(currentPointer > 30){
//				sleep(1);
		}
		pthread_mutex_lock(&lock);
		buffer[currentPointer].randomWait = currentElement.randomWait;
		buffer[currentPointer].randomInteger = currentElement.randomInteger;
		buffer[currentPointer] = currentElement;
		currentPointer += 1;
		pthread_mutex_unlock(&lock);
		
	}		
}

void* consumerFunction(void *args){
	struct dualNumbers currentElement;
	while(1){
		while(currentPointer == 0){
//			sleep(1);
		}
		pthread_mutex_lock(&lock);
		printf("current pointer is %d\n", currentPointer);
		currentElement.randomWait = buffer[currentPointer - 1].randomWait;
		currentElement.randomInteger = buffer[currentPointer - 1].randomInteger;
		currentPointer -= 1;
		pthread_mutex_unlock(&lock);
		printf("First Value: %d\n", currentElement.randomInteger);
		sleep(currentElement.randomWait);
		printf("Second Value: %d\n", currentElement.randomWait);	
	}
}

//Source: https://codereview.stackexchange.com/questions/147656/checking-if-cpu-supports-rdrand
//Author: Cody Gray
unsigned int GetRandomViaRDRAND()
{
    unsigned int value;
    __asm__("rdrand  %[value]"
           : [value] "=r" (value)
           :       /* no inputs */
           : "cc"  /* clobbers flags (condition codes) */
           );
    return value;
}