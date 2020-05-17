#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>\

/*Globals*/
int foregroundMode = 0;
int isBackground = 0;

/*Structs*/
typedef struct{
	int background;// 1 is yes, 0 is no
	int end;       // 1 is yes, 0 is no
	int status;    // 1 is error, 0 is fine
	int childProcessId;
} commandValues;

/*Functions*/

void shellLoop();
char *readLine();
void interpreteInput(commandValues *, char *);
void runBuiltIn(commandValues *, char *);
void attemptLinuxCommand(commandValues *, char *);
void sigHandler(int);
void catchSIGINT(int);
void catchSIGTSTP(int);

/*main function*/

int main(){

	struct sigaction SIGTSTP_action = {0};
/*
	SIGINT_action.sa_handler = catchSIGINT;
	sigfillset(&SIGINT_action.sa_mask);
	SIGINT_action.sa_flags = 0;
	SIGTSTP_action.sa_handler = catchSIGTSTP;
	sigfillset(&SIGTSTP_action.sa_mask);
	SIGTSTP_action.sa_flags = 0;
*/

	if(signal(SIGTSTP, sigHandler) == SIG_ERR){
		write(1, "problem with signals\n", 21);
	}

	shellLoop();	
	printf("the HOME variable is: %s\n", getenv("HOME"));
	printf("the PATH variable is: %s\n", getenv("PATH"));
	return 0;
}

/*  void shellLoop();
*   This functions primary purpose is to be the loop that maintains the shell
*   Inside this function, we will call functions to read, write, and call
*/  

void sigHandler(int signo){
	if(signo == SIGTSTP){
		char* message = "Changing foreground mode to:";
		char* on = "on \n";
		char* off = "off \n";
		fflush(stdout);
		write(1, message, 20);
		if(foregroundMode == 0){
			foregroundMode = 1;
			write(1, on, 4);
		}else{
			foregroundMode = 0;
			write(1, off, 5);
		}

	}
}

void shellLoop(){
	commandValues *currentValue;
	currentValue = malloc(sizeof(commandValues));
	// This will check if the end function has been called yet
	(*currentValue).end = 0;
	(*currentValue).background = 1;
	while((*currentValue).end == 0){
		//Insert check waitpid() for foreground child to run
		char * input;
		if((*currentValue).background == 0){
			int returnval;
			returnval = waitpid((*currentValue).childProcessId, 0, 0);
		}
		(*currentValue).status = 0;
		input = readLine();
		interpreteInput(currentValue, input);

		free(input);
	}
}

/* void interpreteInput(commandValues *, char *)
*  This function will take the input and run the appropriate functions
*/

void interpreteInput(commandValues *inputValues, char *inputArray){
	int fd[2];
	pipe(fd);
	int pid = fork();
	if(pid > 0){ 
		//PARENT'S CODE
		int childId;
		read(fd[0], &childId, sizeof(childId));
		(*inputValues).childProcessId = childId;
		close(fd[1]);
		close(fd[0]);
		if(inputArray[0] == 'c' && inputArray[1] == 'd'){
			if(strlen(inputArray) == 2){
				chdir(getenv("HOME"));
			}else{
				if(strlen(inputArray) > 3){
					chdir((inputArray + 3));
				}
			}

			return;
		}
		int length = strlen(inputArray);
		if(length > 2){
			if(inputArray[(length - 1)] == '&' && inputArray[(length - 2)] == ' '){
				// we know this wants to be run in the background
				(*inputValues).background = 1;
				return;
			}
		}
		(*inputValues).background = 0;
		return;
	} 
	// CHILD'S CODE

	//sending child proccess id to parent
	int childId = getpid();
	write(fd[1], &childId, sizeof(childId));
	close(fd[1]);
	close(fd[0]);

	//This is handeld elsewhere
	if(inputArray[0] == 'c' && inputArray[1] == 'd'){
		exit(0);
	}

	//This is printing out the background process id if background
	int length = strlen(inputArray);
	if(foregroundMode == 0){
		if(length > 2){
			if(inputArray[(length - 1)] == '&' && inputArray[(length - 2)] == ' '){
				char* tmp;
				tmp = malloc(sizeof(childId) + 1);
				sprintf(tmp, "%d\0", childId);
				fflush(stdout);
				write(1, "background pid is ", 18);
				write(1, tmp, sizeof(tmp));
				write(1, "\n", 1);
				free(tmp);
			}
		}
	}
	runBuiltIn(inputValues, inputArray);

	//Get the command for system check
	attemptLinuxCommand(inputValues, inputArray);
}

/*  void attemptLinuxCommand(commandValues *, char *)
*
*/

void attemptLinuxCommand(commandValues *inputValues, char *inputArray){
	//First we will grab the function from the array
	int firstSpace = 0;
	int numUntilSpace = 0;
	//This is getting how many characters the first param is
	while(firstSpace == 0){
		if(inputArray[numUntilSpace] == ' ' || inputArray[numUntilSpace] == '\0'){
			firstSpace = 1;
		}else{
			numUntilSpace++;
		}
	}
	//Here we are using our knowledge of the num of chars to grab the first elem of input
	char *valueCheck;
	char *commandString;
	commandString = malloc(numUntilSpace*sizeof(char));
	int i;
	for(i = 0; i < numUntilSpace; i++){
		commandString[i] = inputArray[i];
	}
	valueCheck = malloc(sizeof(char)*(7 + numUntilSpace));
	strcat(valueCheck, "which ");
	strcat(valueCheck, commandString);

	valueCheck[(6 + numUntilSpace)] = '\0';
	//Get devNull to dump stdout or error from system call
	int devNull = open("/dev/null", "w");
	int stdoutfd = dup(1);
	int stderrfd = dup(2);
	dup2(devNull, 1);
	dup2(devNull, 2);

	//Here we are checking if the function exists or not in the path variable
	if(system(valueCheck)){
		//DOESN'T EXIST IN PATH
		dup2(stdoutfd, 1);
		dup2(stderrfd, 2);
		fflush(stdout);
		write(1, commandString, strlen(commandString));
		write(1, ": no such file or directory\n", 28);
		(*inputValues).status = 1;
	}else{
		//EXISTS
		//We need to get number of arguments
		int i, j;
		j = 1;
		int arrayLength = strlen(inputArray);
		for(i = 1; i < arrayLength; i++){
			if(inputArray[i] == ' ' && inputArray[i-1] != ' '){
				j++; //j is num of args
			}
		}
		char **argv;
		argv = malloc(j * sizeof(char*));
		//We need to make list of arguments
		int l = 1;
		argv[0] = inputArray;
		for(i = 1; i < (arrayLength - 1); i++){
			if(*(inputArray + i) == ' ' && *(inputArray + i + 1) != ' '){
				*(inputArray + i) = '\0';
				argv[l] = (inputArray + i + 1);
				l++;
			}
		}
		//Change output for the functions back to normal
		dup2(stderrfd, 2);
		dup2(stdoutfd, 1);
		fflush(stdout);
		//write(1, "exists\n", 7);
		(*inputValues).status = 0;

		//get the system(valuecheck as a char*);
		execvp(commandString, argv);
	}
	free(commandString);
	free(valueCheck);
	exit(0);
}

/*  void runBuiltIn(commandValues *, char *)
*
*/

void runBuiltIn(commandValues *inputValues, char *inputArray){
	if(inputArray[0] == '#'){
		exit(0);
	}
	if(strcmp(inputArray, "exit") == 0){
		(*inputValues).end = 1; 
		exit(0);
	}
	/*if(inputArray[0] == 'c' && inputArray[1] == 'd'){	
		chdir(getenv("HOME")); // need to change directory
		exit(0);
	}*/
	if(strcmp(inputArray, "status") == 0){
		printf("exit value %d\n", (*inputValues).status); //need to pipe this back
		exit(0);
	}
}

/*  char * readLine()
*   This function will use getline to read user input
*   This input will be returned as a dynamic char array
*/

char *readLine(){
	//will wait for shell to get any input
	while(1){
		size_t bufsize = 0;
		int numCharacters;
		char * lineEntered = NULL;
		fflush(stdout);
		write(1, ": ", 2);
		numCharacters = getline(&lineEntered, &bufsize, stdin);
		char * savedInput;
		if((numCharacters - 1) > 0){
			//saving input from buffer to string
			savedInput = malloc((numCharacters - 1)*sizeof(char));
			int i;
			for (i = 0; i < (numCharacters - 1); i++)
			{
				savedInput[i] = lineEntered[i];
			}
			savedInput[(numCharacters - 1)] = '\0';
			fflush(stdout);

			return savedInput;
		}	
	}
}






main();
