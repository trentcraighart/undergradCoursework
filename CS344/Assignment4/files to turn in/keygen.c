#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
* Filename: keygen
* Input:    Will take in one integer 
* Output:   Will output a key string the length of input integer + 1
*/


int main(int argc, char const *argv[]){
	//Here we will seed our time for random
	srand(time(NULL));

	//First we will check if correct num of parameters
	if(argc == 2){
		//Next we will check if the second parameter is an integer
		int isValid, i;
		isValid = 1;
		for(i = 0; i < strlen(argv[1]); i){
			//Checking if char is an integer or space
			if(argv[1][i] > 47 && argv[1][i] < 58){
				i++;
			}
			//Value besides int was found
			else{
				char* errorInvalidParamType;
				errorInvalidParamType = "error: improper parameter type\n";
				write(2, errorInvalidParamType, strlen(errorInvalidParamType));
				exit(1);
			}
		}
		//We have varified input as integer
		//We will now convert that into a true integer
		int numParameters, j;
		numParameters = 0;
		j = 1; // j will be 10 multiple
		for(i = strlen(argv[1]); i > 0; i--){
			//below we convert ascii to int, then mult by j, were working from tail to head
			numParameters = numParameters + (j * (argv[1][(i-1)] - 48));
			j = j * 10;
		}
		//We now have our final number of parameters to print
		int r;
		char randLetter;
		for(i = 0; i < numParameters; i++){
			fflush(stdout);
			r = rand() % 27;
			if(r == 26){
				randLetter = 32;
			}else{
				randLetter = (r + 65);
			}
			write(1, &randLetter, 1);		
		}
		write(1, "\n", 1);
		exit(0);
		
	//Keygen was given an invalid number of parameters
	}else{
		char* errorInvalidParamNum;
		errorInvalidParamNum = "error: improper number of arguments\n";
		write(2, errorInvalidParamNum, strlen(errorInvalidParamNum));
		exit(1);
	}
}

