#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

/*Globals*/
int numChildren = 0;
int running  = 0;
int ins = 0;
int del = 0;

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues
void sigHandler(int signo){
	//Cleans up children on termination
	if(signo == SIGCHLD){
		wait();
	}
}

/*Structs*/
struct node{
	int v;
	struct node* next;
};
typedef struct node node;

/*Functions*/
void *finder(void*);
void *inserter(void*);
void *deleter(void*);
void *reader();

/*Globals*/
node* head;


int main(int argc, char *argv[]){
	printf("The base of the list is at spot 0 with value 0\n");
	head = malloc(sizeof(head));
	head->v = 0;
	head->next = NULL;

	//Signal handeler for children
	struct sigaction SIGCHLD_action = {0};
	signal(SIGCHLD, sigHandler);

	int listenSocketFD, establishedConnectionFD, portNumber, charsRead;
	socklen_t sizeOfClientInfo;
	//char buffer[256];
	struct sockaddr_in serverAddress, clientAddress;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding"); //MIGHT NEED LOOP HERE TO GET PORT
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
	int findingConnection;
	pthread_t newThread;	
	while(1){
		// Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		//This is here to keep more then 5 connections from being formed at once
		findingConnection = 1;
		while(findingConnection == 1){
			if(numChildren < 5){
				establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
				//printf("connection accepted\n");
				findingConnection = 0;
			}
		}
		numChildren++;

		//Building Fork for Children and Parents

		//******************************************************************************
		//Here is where our server will comunicate with the client
		int bytesRec, val;
		char type;
		bytesRec = recv(establishedConnectionFD, &val, sizeof(int), 0);
		bytesRec = recv(establishedConnectionFD, &type, sizeof(char), 0);
		//******************************************************************************


		printf("calling pthread for value %c\n", type);		
		if(type == 'i'){

			pthread_create(&newThread, NULL, &inserter, &val);
		}
		if(type == 'd'){
			del = 1;
			pthread_create(&newThread, NULL, &deleter, &val);
		}	
		if(type == 'f'){
			pthread_create(&newThread, NULL, &finder, &val);
		}
		if(type == 'p'){
			pthread_create(&newThread, NULL, &reader, NULL);

			
		}
		close(establishedConnectionFD); // Close the existing socket which is connected to the client
		numChildren--;	
	} 
}

void *reader(){
	while(del == 1){
		sleep(1);
	}
	running++;
	node* traverseNode;
	traverseNode = head;
	int j = 0;
	printf("The contents of the list:\n");
	while(traverseNode != NULL){
		printf("spot %d is %d\n", j, traverseNode->v);
		j++;
		traverseNode = traverseNode->next;
	}
	running--;
}

void *finder(void *v){
	while(del == 1){
		sleep(1);
	}
	running++;
	int *val1 = v;
	int val = *val1;
	node *curNode = head;
	int i = 0;
	int found = 0;
	while(curNode != NULL){
		if(val == curNode->v){
			printf("%d was found at spot %d\n", val, i);
			found = 1;
		}
		i++;
		curNode = curNode->next;
	}
	if(found == 0){
		printf("Couldn't find val %d\n", val);
	}
	running--;			
}

void *inserter(void *v){
	while(ins == 1 || del == 1){
		sleep(1);
	}
	ins = 1;
	running++;	
	int *val1 = v;
	int val = *val1;
	printf("appending value %d\n", val);
	node *curNode = head;
	node *newNode;
	newNode = malloc(sizeof(node));
	newNode->v = val;
	while(curNode->next != NULL){
		curNode = curNode->next;
	}
	curNode->next = newNode;
	running--;		
	ins = 0;
}

void *deleter(void *l){
	while(running > 0){
		sleep(1);
	}
	del = 1;
	running++;	
	int *location1 = l;
	int location = *location1;
	node *prev = head;
	node *cure = prev->next;
	node *temp;
	int i = 1;
	if(cure == NULL && location == 0){
		printf("Can't delete last element\n");
	}
	if(cure != NULL && location == 0){
		temp = prev;
		head = cure;
		free(temp);
		printf("deleted element 0\n");
	}
	if(location > 0){
		while(cure != NULL){
			if(i == location){
				prev->next = cure->next;
				free(cure);
				cure = prev;
			}
			cure = cure->next;
			prev = prev->next;			
			i++;
		}
		printf("deleted element %d\n", location);
	}
	running--;	
	del = 0;	
}