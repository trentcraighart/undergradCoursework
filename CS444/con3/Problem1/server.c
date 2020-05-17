#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

/*Globals*/
int numChildren = 0;
int maxed = 0;

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

void sigHandler(int signo){
	//Cleans up children on termination
	if(signo == SIGCHLD){
		wait();
		numChildren--;
		if(numChildren == 0){
			maxed = 0;
		}
	}
}

int main(int argc, char *argv[]){

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

	while(1){
		// Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		//This is here to keep more then 5 connections from being formed at once
		int findingConnection = 1;
		while(findingConnection == 1){
			if(maxed == 0){
				establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
				//printf("connection accepted\n");
				findingConnection = 0;
				if(numChildren == 2){
					maxed = 1;
				}
			}
		}

		//Building Fork for Children and Parents
		int pid = fork();
		if(pid > 0){
			numChildren++;
		}else{
			//******************************************************************************
			//Here is where our server will comunicate with the client
			int bytesRec, time;
			bytesRec = recv(establishedConnectionFD, &time, sizeof(int), 0);

			printf("Request to sleep for %d seconds\n", time);
			sleep(time);
			printf("Done sleeping for %d seconds\n", time);
			
			//******************************************************************************
			close(establishedConnectionFD); // Close the existing socket which is connected to the client
			close(listenSocketFD); // Close the listening socket
			exit(0);
		}
	} 
}
