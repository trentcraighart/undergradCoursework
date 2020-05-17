#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

/*Globals*/
int foregroundMode = 0;
int isBackground = 0;
int isChild = 0;
int prevError = 0;
int currentPid = NULL;

/*Structs*/
typedef struct{
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


/*main function*/

int main(){

	struct sigaction SIGTSTP_action = {0};
	struct sigaction SIGUSR1_action = {0};
	struct sigaction SIGUSR2_action = {0};
	struct sigaction SIGCHLD_action = {0};	
	struct sigaction SIGINT_action = {0};

	//setting up handelers for signals
	signal(SIGTSTP, sigHandler);
	signal(SIGUSR1, sigHandler);
	signal(SIGUSR2, sigHandler);
	signal(SIGCHLD, sigHandler);
	signal(SIGINT, sigHandler);


	shellLoop();	
	return 0;
}

/*  void shellLoop();
*   This functions primary purpose is to be the loop that maintains the shell
*   Inside this function, we will call functions to read, write, and call
*/  

void sigHandler(int signo){
	//SIGSTP
	if(signo == 20){
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
	//proccess failed SIGUSR1
	if(signo == 10){
		prevError = 1;
	}
	//process is fine SIGUSR2
	if(signo == 12){
		prevError = 0;
	}
	//If its a child proccess during a SIGINT, it'll terminate
	if(signo == SIGINT){
		if(isChild == 1){
			kill(getpid(), SIGKILL);
		}else{
			char* message = " terminating all child proccess\n";
			fflush(stdout);
			write(1, message, strlen(message));
		}
	}
	//handles child termination, may he rest in piece
	/*
            *       *
*		*       *          *
         _______    *
    *   /       \      *
        | R.I.P |   _      *
   *    |       |  ( )  *   
	    | Child | ( O ) 
  	  * |  And  |  _|_
	    | Friend|  \_/     */   
	if(signo == SIGCHLD){
		if(isChild == 0){
			if(currentPid == NULL){
				wait();
			}
		}
	}
}

void shellLoop(){
	commandValues *currentValue;
	currentValue = malloc(sizeof(commandValues));
	// This will check if the end function has been called yet
	(*currentValue).end = 0;
	isBackground = 1;
	while((*currentValue).end == 0){
		//Insert check waitpid() for foreground child to run
		char * input;
		if(isBackground == 0){
			int returnval;
			returnval = waitpid((*currentValue).childProcessId, 0, 0);
			currentPid = NULL;
		}
		isBackground = 0;
		input = readLine();
		interpreteInput(currentValue, input);
		free(input);
	}
}

/* void interpreteInput(commandValues *, char *)
*  This function will take the input and run the appropriate functions
*/

void interpreteInput(commandValues *inputValues, char *inputArray){
	//setting up pipes and forks
	int fd[2];
	pipe(fd);
	int pid = fork();
	//POST FORK
	if(pid > 0){ 
		//PARENT'S CODE
		int childId;
		read(fd[0], &childId, sizeof(childId));
		(*inputValues).childProcessId = childId;
		currentPid = childId;
		close(fd[1]);
		close(fd[0]);
		//Deals with changing directories
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
				if(foregroundMode == 0){
					isBackground = 1;
				}
				return;
			}
		}
		isBackground = 0;
		return;
	} 
	// CHILD'S CODE
	isChild = 1;
	//sending child proccess id to parent via pipe
	int childId = getpid();
	write(fd[1], &childId, sizeof(childId));
	close(fd[1]);
	close(fd[0]);

	//This is handeld elsewhere
	if(inputArray[0] == 'c' && inputArray[1] == 'd'){
		exit(0);
	}

	//Check if there is an &
	int length = strlen(inputArray);
	if(length > 2){
		if(inputArray[(length - 1)] == '&' && inputArray[(length - 2)] == ' '){
			isBackground = 1;
		}
	}	

	//This is printing out the background process id if background
	if(foregroundMode == 0 && isBackground == 1){
		char* tmp;
		tmp = malloc(sizeof(childId) + 1);
		sprintf(tmp, "%d\0", childId);
		fflush(stdout);
		write(1, "background pid is ", 18);
		write(1, tmp, sizeof(tmp));
		write(1, "\n", 1);
		free(tmp);

	}
	//Checks all built in functions
	runBuiltIn(inputValues, inputArray);
	//Get the command for system check
	//is running well until proven otherwise
	kill(getppid(), SIGUSR2);	
	attemptLinuxCommand(inputValues, inputArray);
}

/*  void attemptLinuxCommand(commandValues *, char *)
*
*/

void attemptLinuxCommand(commandValues *inputValues, char *inputArray){
	//First we will grab the function from the array
	int firstSpace = 0;
	int numUntilSpace = 0;
	while(firstSpace == 0){
		if(inputArray[numUntilSpace] == ' ' || inputArray[numUntilSpace] == '\0'){
			firstSpace = 1;
		}else{
			numUntilSpace++;
		}
	}
	char *valueCheck;
	char *commandString;
	commandString = malloc(numUntilSpace*sizeof(char));
	int i;
	for(i = 0; i < numUntilSpace; i++){
		commandString[i] = inputArray[i];
	}
	//With the command, we are concatanating a which function
	valueCheck = malloc(sizeof(char)*(7 + numUntilSpace));
	strcat(valueCheck, "which ");
	strcat(valueCheck, commandString);
	valueCheck[(6 + numUntilSpace)] = '\0';

	//Get devNull to dump stdout or error from system call
	int devNull = open("/dev/null", O_WRONLY);
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
		kill(getppid(), SIGUSR1);
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
		//Here we know we need to ignore the & call
		if(isBackground == 1){
			j--; //Here we are ignoring the final parameter
			inputArray[(arrayLength - 1)] = '\0'; //changing & to null
		}
		int l = 1;
		argv[0] = inputArray;
		for(i = 1; i < (arrayLength - 1); i++){
			if(*(inputArray + i) == ' ' && *(inputArray + i + 1) != ' '){
				*(inputArray + i) = '\0';
				argv[l] = (inputArray + i + 1);
				l++;
			}
		}
		//If we are running in foregroud, fix the output stream
		if(foregroundMode == 1 || isBackground == 0){
			dup2(stderrfd, 2);
			dup2(stdoutfd, 1);
			fflush(stdout);	
		}

		int cutFromArgs = 0;
		if(isBackground == 1){
			cutFromArgs++;
		}

		//Changing input and output for > and < operators
		for(i = 0; i < l; i++){
			if(strcmp(argv[i], ">") == 0){
				int outputLocation; 
				outputLocation = open(argv[i+1], O_CREAT| O_TRUNC | O_WRONLY, 0666);
				dup2(outputLocation, 1);
				cutFromArgs = cutFromArgs + 2;
			}
			if(strcmp(argv[i], "<") == 0){
				int inputLocation;
				inputLocation = open(argv[i+1], O_RDONLY | O_CREAT, 0666);
				dup2(inputLocation, 0);
				cutFromArgs = cutFromArgs + 2;
			}
		}
		int numPassingArgs;
		numPassingArgs = l - cutFromArgs;
		//printf("num of args tot%d, passing in %d\n", l, numPassingArgs);
		char** argvPassing;
		argvPassing = malloc(sizeof(char*)*numPassingArgs);
		for(i = 0; i < numPassingArgs; i++){
			argvPassing[i] = argv[i];
		}

		//get the system(valuecheck as a char*);
		if(execvp(commandString, argvPassing) == -1){
			kill(getppid(), SIGUSR1);			
		}
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
	if(strcmp(inputArray, "exit") == 0 || strcmp(inputArray, "quit") == 0){
		kill(getppid(), SIGKILL);
		exit(0);
	}
	if(strcmp(inputArray, "status") == 0){
		char tmp[2];
		sprintf(tmp, "%d\n", prevError);
		fflush(stdout);
		write(1, "exit value ", 11);
		write(1, tmp, 2);
		fflush(stdout);
		kill(getppid(), SIGUSR2);
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

			//Converting any $$ into the current proccess id
			i = 1;
			while(i < numCharacters){
				if(savedInput[i-1] == '$' && savedInput[i] == '$'){
					char* tmp;
					int currentId = getpid();
					tmp = malloc(sizeof(currentId));
					sprintf(tmp, "%d", currentId);
					char* modInput = malloc((numCharacters - 3)*sizeof(char) + (strlen(tmp)));
					//Get up to the $$
					int j;
					for(j = 0; j < (i - 1); j++){
						modInput[j] = savedInput[j];
					}
					//Replacing the $$
					int k;
					for(k = 0; k < strlen(tmp); k++){
						modInput[k+j] = tmp[k];
					}
					//get rest of the original string
					i = k+j;
					int stringEnd = (numCharacters - 2 + strlen(tmp));
					int l;
					for(l = i; l < stringEnd; l++){
						j++;
						modInput[l] = savedInput[j];
					}
					return modInput;	
				}
				i++;
			}

			//fflush(stdout);
			//printf("\n~~~~~ %s ~~~~~\n", savedInput);
			return savedInput;
		}	
	}
}






main();
