#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


/*Globals*/
char **phil;
char spoons[5];
char status[5];
pthread_t tid[5];
pthread_mutex_t lock;

/*Declarations*/
void* philFunction(void*);
void think(int);
void get_spoons(int);
void eat(int);
void put_spoons(int);

int main(int argc, char const *argv[])
{
	int i;
	pthread_mutex_init(&lock, NULL);
	srand(time(NULL));

	//char **phil;
	phil = malloc(sizeof(char*)*5);
	for(i = 0; i < 5; i++){
		phil[i] = malloc(sizeof(char)*16);
	}
	phil[0] = "Plato";
	phil[1] = "Aristotle";
	phil[2] = "Nietzshe";
	phil[3] = "Rousseau";
	phil[4] = "Kanye West";

	//char spoons[5];
	for(i = 0; i < 5; i++){
		spoons[i] = 'O';
	}

	int pid;
	for(i = 0; i < 5; i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;
		pthread_create(&(tid[i]), NULL, &philFunction, arg);
	}

	while(1){
		printf("\n[%c]   [%c]   [%c]   [%c]   [%c]\n", status[0], status[1], status[2], status[3], status[4]);
		printf("   [%c]   [%c]   [%c]   [%c]   [%c]\n", spoons[1], spoons[2], spoons[3], spoons[4], spoons[0]);
		printf("Top row is philosiphers - Bottom row are spoons\n");
		printf("Key: [T] = Thinking, [E] = Eating, [W] = Waiting, [O] = Valid Spoon, [X] = Used Spoon\n");
		sleep(5);
	}

	return 0;
}

void* philFunction(void *arg){
	int i = *((int *) arg);
	free(arg);
	while(1){
		think(i);
		get_spoons(i);
		eat(i);
		put_spoons(i);
	}
}

void think(int person){
	status[person] = 'T';
	int r;
	r = (rand() % 20) + 1;
	printf("%s is thinking for %d seconds\n", phil[person], r);

	sleep(r);
}

void get_spoons(int person){
	int spoon1, spoon2;
	spoon1 = person;
	spoon2 = person + 1;
	if(person == 4){
		spoon2 = 0;
	}
	printf("%s is waiting for spoons\n", phil[person]);
	while(spoons[spoon1] == 'X' || spoons[spoon2] == 'X'){
		status[person] = 'W';
		sleep(1);
	}
	pthread_mutex_lock(&lock);
//	printf("%s is grabbing two spoons\n", phil[person]);
	status[person] = 'E';
	spoons[spoon1] = 'X';
	spoons[spoon2] = 'X';
	pthread_mutex_unlock(&lock);
}

void eat(int person){
	int r;
	r = (rand() % 8) + 2;
	printf("%s is eating for %d seconds\n", phil[person], r);
	sleep(r);
	status[person] = 'T';
}

void put_spoons(int person){
	int spoon1, spoon2;
	spoon1 = person;
	spoon2 = person + 1;
	if(person == 4){
		spoon2 = 0;
	}	
	pthread_mutex_lock(&lock);
//	printf("%s is placing two spoons\n", phil[person]);
	spoons[spoon1] = 'O';
	spoons[spoon2] = 'O';
	pthread_mutex_unlock(&lock);
}

