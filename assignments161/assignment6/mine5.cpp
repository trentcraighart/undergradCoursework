/***
 *Program Filename: minesweeper.cpp
 *Author: Trent Vasquez
 *Date: 3/xx/2016
 *Description: This program will play minesweeper
 **/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

//Prototypes
int testcommand(int, char*[], int *, int *, int *);
int player_num();
char ** makeboard(int, int , int);
void fillnum(char **, int, int, int, int);
void print(char **, int, int);
void playgame(char **, int, int);
void pickchoice(char **, char **, int , int, int *);
void checknum(char **, char **, int, int, int **){

int main(int argc, char *argv[]){
	srand (time(NULL));
	int valid, run = 1, row, col, bom, i;
	char **board;
	while(run==1){
		valid = testcommand(argc, argv, &row, &col, &bom);
		if(valid==1)
			return 0;
		board = makeboard(row, col, bom);
		

		print(board, row, col);
		
		playgame(board, row, col);	
	
		return 0; //remove this later
	}
		
	return 0;


}

void playgame(char **board, int row, int col){
	int i, j, cor;	
	char** gameboard = new char*[row];
	for(i=0; i<row; ++i)
		gameboard[i] = new char[col];
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			gameboard[i][j] = '-';
		}
	}
	while(cor<(row*col)){
		if(cor==-1){
		cout << "Game Over" << endl;
		break;
		}
		pickchoice(gameboard, board, row, col, &cor);
	}
	//Insert restart game function here!
}
	
void pickchoice(char **gameboard, char **board, int row, int col, int *cor){
	int choice;
	print(gameboard, row, col);
	cout << "1) reveal a spot\n2) place a flag" << endl;
	choice = player_num();
	if(choice==1){
	}
	if(choice==2){
	}

}

void checknum(char **gameboard, char **board, int row, int col, int **cor){

}





















/***
 * Function: player_num
 * Description: Asks the user for a number of players between 1-2
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: The user will be able to choose a value between 1-2
 **/

int player_num(){
	int start, valuef;
	string num;
	start = 1;
	while(start==1){
		cin >> num;
		if(num=="1" || num=="2"){
			valuef = atoi(num.c_str());
			return valuef;
		}else{
			cout << "Invalid input, New input: ";
		}
	}
}

/***
 * Function: makeboard 
 * Description: this function takes the command line arguments and forms them into a board with bombs
 * Parameters: command line arguments row, col, bom
 * Pre-Conditions: the command line areguments are correct
 * Post-Conditions: will return the completed board as a char[][]
 **/

char** makeboard(int row, int col, int bom){
	int i, j, r, c;
	char** board = new char*[row];
	for(i=0; i<row; ++i)
		board[i] = new char[col];
	for(i=0;i<bom;){
		r = rand() % row;
		c = rand() % col;
		if(board[r][c] != 'b'){
			board[r][c] = 'b';
			i++;
		}	
	}	
	for(i=0;i<row;){
		for(j=0;j<col;){
			fillnum(board, i, j, row, col);
			j++;
		}
		i++;
	}
	return board;
}

/***
 * Function: fillnum
 * Description: This function will take the board full of bombs and populate it with numbers
 * Parameters: the board, the rows/col, the current cell (i,j)
 * Pre-Conditions: the board
 * Post-Conditions: all spots on the board will have a number or a bomb
 **/

void fillnum(char **board, int i, int j, int row, int col){
	int k, l, b = 0;
	char num;
	for(k=-1;k<2;k++){
		for(l=-1;l<2;l++){
			if(i+k >= 0 && i+k <= row-1 && j+l >= 0 && j+l <= col-1){
				if(board[i+k][j+l]=='b'){
					b++;
				}
			}
		}
	}
	if(board[i][j] != 'b'){
		board[i][j] = b + '0';
	}
}

/***
 * Function: print
 * Description: this takes a board and prints it for the user
 * Parameters: a 2d array board, the row, the col
 * Pre-Conditions: the row and col are positive ints 
 * Post-Conditions: print to the screen the board 
 **/

void print(char **board, int row, int col){
	int i, j;
	cout << "*  ";
	for(j=0;j<col;j++){
		if(j<10)
			cout << " " << j << " ";
		else
			cout << j << " ";
	}
	cout << "" << endl;
	for(i=0;i<row;i++){
		if(i<10)
			cout << i << "  ";
		else
			cout << i << " ";
		for(j=0;j<col;j++){
			cout << "|" << board[i][j] << "|";
		}
		cout << "" << endl;
	}
}

/***
 * Function: testcommand
 * Description: this tests the users command line input
 * Parameters: the argument count, the argument values, the row, the col, the bom
 * Pre-Conditions: the input needs to be put in pairs with the number
 * Post-Conditions: This will modify row, col, and bom by reference, will return 1 for bad input, 0 for good
 **/ 

int testcommand(int argc, char *argv[], int* row, int* col, int* bom){
	int value = 0, i, a = 0, b = 0, c = 0;
	if(argc != 7){
		cout << "Bad Peramiters value count" << endl;
		return 1;
	}
	for(i=0;i<7;i++){
		if(argv[i][0] == '-' && argv[i][1] == 'r'){
			*row = atoi(argv[i+1]);
			a = 1;
			value++;
		}
		if(argv[i][0] == '-' && argv[i][1] == 'c'){
			*col = atoi(argv[i+1]);
			value++;
			b = 1;
		}
		if(argv[i][0] == '-' && argv[i][1] == 'b'){
			*bom = atoi(argv[i+1]);
			value++;
			c = 1;
		}
	}
	if(value==3 && a == 1 && b == 1 && c == 1){
		return 0;
	}else{
		cout << "Bad Peramiters incorrect amount of values" << endl;
		return 1;
	}
}








//Format for functions
/***
 * Function: 
 * Description: 
 * Parameters: 
 * Pre-Conditions: 
 * Post-Conditions: 
 **/
