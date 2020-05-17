/***
 *Program Filename: minesweeper.cpp
 *Author: Trent Vasquez
 *Date: 3/xx/2016
 *Description: This program will play minesweeper
 **/
#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

//Prototypes
int testcommand(int, char*[], int *, int *, int *);
char ** makeboard(int, int , int);

int main(int argc, char *argv[]){
	srand (time(NULL));
	int valid, run = 1, row, col, bom, i;
	char **board;
	while(run==1){
		valid = testcommand(argc, argv, &row, &col, &bom);
		if(valid==1)
			return 0;
		board = makeboard(row, col, bom);
		cout << "Board [0][1] is " << endl;
		cout << board[0][1] << endl;
		



		return 0; //remove this later
	}
		
	return 0;


}

char** makeboard(int row, int col, int bom){
	int i, j, r, c;
	char** board = new char*[row];
	for(i=0; i<row; ++i)
		board[i] = new char[col];
	//char ** board;
	for(i=0;i<bom;){
		r = rand() % row;
		c = rand() % col;
		cout << "finished random" << endl;
		if(board[r][c] != 'b'){
			cout << "Placing the bomb" << endl;
			board[r][c] = 'b';
			cout << "Placed bomb" << endl;
			i++;
		}	
		cout << i << endl;
	}	
	for(i=0;i<row;){
		for(j=0;j<col;){
			j++;
		}
		i++;
	}
	cout << "board[0][1]" << endl;
	cout << board[0][1] << endl;
	cout << "board" << endl;
	cout << board << endl;

	return board;
	

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
		cout << "attempt: " << i << endl;
		if(argv[i][0] == '-' && argv[i][1] == 'r'){
			cout << "-r is a good parameter" << endl;
			*row = atoi(argv[i+1]);
			a = 1;
			value++;
		}
		if(argv[i][0] == '-' && argv[i][1] == 'c'){
			cout << "-c is a good parameter" << endl;
			*col = atoi(argv[i+1]);
			value++;
			b = 1;
		}
		if(argv[i][0] == '-' && argv[i][1] == 'b'){
			cout << "-b is a good parameter" << endl;
			*bom = atoi(argv[i+1]);
			value++;
			c = 1;
		}
	}
	for(i=0;i<argc;i++){
		cout << argv[i] << endl;
	}
	cout << argc << endl;
	cout << value << endl;
	cout << "row " << *row << endl;
	cout << "col " << *col << endl;
	cout << "bom " << *bom << endl;
	if(value==3 && a == 1 && b == 1 && c == 1){
		cout << "Correct Peramiters" << endl;
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
