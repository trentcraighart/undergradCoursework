#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues

int main(int argc, char *argv[])
{
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	//char buffer[256];

	//******************************************************************
	//Here we will check what is being passed to the the program
	if (argc < 4) { fprintf(stderr,"USAGE: client val type port\nfunction types are [i]sert, [d]elete, [f]ind, [p]rint\n"); exit(1); } // Check usage & args

	//argv[1] Parameter
	//argv[2] type of function
	//argv[3] needs to be port number

	//note pointers are set to end of file after this
	//******************************************************************

	// Set up the server address struct
	char* hostLocation = "localhost";
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname(hostLocation); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");


	//******************************************************************************
	//Here is where our client will send files to the server
	int bytesSent, val;
	char type = argv[2][0];
	val = atoi(argv[1]);
	bytesSent = send(socketFD, &val, sizeof(val), 0);
	bytesSent = send(socketFD, &type, sizeof(char), 0);


	//******************************************************************************

	close(socketFD); // Close the socket
	exit(0);
	return 0;	
}