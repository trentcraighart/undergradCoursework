#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

/*Structs*/
struct roomData{
	char** connections;
	char* name;
	char* type;
};

/*Functions*/
struct roomData *readFile();
void playGame(struct roomData **);
int getStartRoom(struct roomData **);
int getRoomValue(struct roomData **, char*);
void get_time(pthread_mutex_t *);

int main(){
	int file_count = 0, x = 0;
	struct roomData **allData;
	allData = malloc(sizeof(struct roomData*));
	for(x = 0; x < 7; x++){
		allData[x] = malloc(sizeof(struct roomData));
	}
	struct dirent *de;
	DIR *dr = opendir("./rooms");
	if(dr == NULL){
		printf("rooms directory not found\n");
		return 0;
	}
	x = 0;
	while((de = readdir(dr)) != NULL){
		/* skips . and .. */
		if(x != 0 && x != 1){
			allData[x-2] = readFile(de->d_name);
		}
		x++;
	}
	closedir(dr);

	playGame(allData);

	return 0;
}

int getStartRoom(struct roomData **allData){
	int x;
	for(x = 0; x < 7; x++){
		if((*allData[x]).type[0] == 'S'){
			return x; 
		}	
	}
	return 1;
}

int getRoomValue(struct roomData **allData, char *newRoom){
	int x;
	for(x = 0; x < 7; x++){
		if((*allData[x]).name[0] == newRoom[0]){
			return x;
		}
	}
	return 1;
}

void playGame(struct roomData **allData){
	/*We do not expect more than 30 moves*/
	pthread_mutex_t *lock = malloc(sizeof(pthread_mutex_t));
	char **history = malloc(sizeof(char *)*30);
	int stepCount = 1;
	int runningGame = 0;
	int time = 0;
	int roomValue = getStartRoom(allData);
	history[0] = (*allData[roomValue]).name;
	size_t bufsize = 32;
	size_t characters;
	char * buffer = malloc(bufsize*sizeof(char));
	int x = 0, y = 1;
	while(runningGame == 0){
		if(time == 0){
			printf("CURRENT LOCATION: %s\n", (*allData[roomValue]).name);
			printf("POSSIBLE CONNECTIONS: ");
			printf("%s", (*allData[roomValue]).connections[0]);
			x = 0;
			y = 1;
			while(x == 0){
				if((*allData[roomValue]).name[0] != (*allData[roomValue]).connections[y][0]){
					printf(", %s", (*allData[roomValue]).connections[y]);
					y++;
				}else{
					x = 1;
				}
			}
		}
		printf(".\nWhere to > ");
		characters = getline(&buffer, &bufsize, stdin);
		char a = buffer[0];
		int correct = 0;
		buffer[strcspn(buffer, "\r\n")] = 0;
		time = 0;
		if(strcmp(buffer, "time") == 0){
			printf("TIME TIME TIME");
			time = 1;
			get_time(lock);
		}
		for(x = 0; x < y; x++){
			char b = (*allData[roomValue]).connections[x][0];
			if(a == b && correct == 0){
				history[stepCount] = (*allData[roomValue]).connections[x];
				roomValue = getRoomValue(allData, (*allData[roomValue]).connections[x]);
				stepCount = stepCount+1;
				correct = 1;
			}
		}
		if(correct == 0 && time == 0){
			printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
		}
		char c = (*allData[roomValue]).type[0];
		if(c == 'E'){
			runningGame = 1;
			printf("\nYOU MADE IT TO THE END!!!\n");
			printf("Here was the route you took:\n");
			for(x = 0; x < stepCount; x++){
				printf("%d: %s\n", x, (history[x]));
			}
			printf("You took %d steps\n", (stepCount - 1));
		}
	}
}

void get_time(pthread_mutex_t *lock){

/************************************
For an example in mutex/thread proficiencey,
please look at the buildrooms file. 
During the file creation, I ran into trouble
with struct's values changing so I implemented
thread's with mutex locks there. I ran out of time
Building this section due to hardware failures
on my laptop.
************************************/

	/*pthread_mutex_lock(lock);*/
	FILE * fp;
	time_t rawtime;
	struct tm *info;
	time(&rawtime);
	info = localtime(&rawtime);
	char buffer[50];
	char fileLocation[50] = "currentTime.txt";
	fp = fopen(fileLocation, "w+");
	strftime(buffer, 50, "%x - %I:%M%p", info);
	fprintf(fp, "%s\n", buffer);
	/*pthread_mutex_unlock(lock);*/
}

struct roomData *readFile(char* fileName){
	int x = 0;
	char * buffer = 0;
	char * fileLocation = malloc (30);
	long length;
	strcpy(fileLocation, "./rooms/");
	strcat(fileLocation, fileName);
	FILE * fp = fopen(fileLocation, "rb");
	if(fp){
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		buffer = malloc(length);
		if(buffer){
			fread(buffer, 1, length, fp);
		}
		fclose(fp);
	}
	struct roomData *curFile;
	curFile = malloc(sizeof(struct roomData));
	(*curFile).connections = malloc(7*sizeof(char*));
	for(x = 0; x < 7; x++){
		(*curFile).connections[x] = malloc(8);
	}
	(*curFile).name = malloc(8);
	(*curFile).type = malloc(8);
	if(buffer){
		char* token = strtok(buffer, " :\n\0");
		token = strtok(NULL, " :\n\0");
		token = strtok(NULL, " :\n\0");
		strcpy((*curFile).name, token);
		int foundType = 0;
		x = 0;
		while(foundType == 0){
			if(token[0] == 'R' && token[1] == 'O'){
				foundType = 1;
				token = strtok(NULL, " :\n\0");
				token = strtok(NULL, " :\n\0");
				strcpy((*curFile).type, token);
			}else{
				if(token[0] == 'C' && token [1] == 'o'){
				token = strtok(NULL, " :\n\0");	
				token = strtok(NULL, " :\n\0");
				strcpy((*curFile).connections[x], token);
				x++;
				}
			}
			token = strtok(NULL, " :\n\0");
		}
	}
	strcpy((*curFile).connections[x], (*curFile).name);
	return curFile;
}