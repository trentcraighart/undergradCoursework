/***
 *Program Filename: minesweeper.cpp
 *Author: Trent Vasquez
 *Date: 3/11/2016
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
int test_string();
char ** makeboard(int, int , int);
void fillnum(char **, int, int, int, int);
void print(char **, int, int);
void playgame(char **, int, int, int);
void pickchoice(char **, char **, int , int, int *, int *);
void checknum(char **, char **, int, int, int **, int, int);
void checkflag(char **, char **, int, int, int **, int **, int, int);
void checkpoint(int *, int *, int, int);
void reczero(char **, char **, int, int, int, int);
void restart(int *, int *, int *);

int main(int argc, char *argv[]){
	srand (time(NULL));
	int valid, run = 1, row, col, bom, i;
	char **board;
	valid = testcommand(argc, argv, &row, &col, &bom);
	cout << "Win by having all of the bombs flagged with no mistakes!" << endl;
	while(run==1){
		if(valid==1)
			return 0;
		board = makeboard(row, col, bom);
			
		playgame(board, row, col, bom);	
		cout << "Press 1 to play again, 2 to quit" << endl;	
		run = player_num();	
		if(run==2)
			return 0;
		restart(&row, &col, &bom);
	}
	
	cout << "Thanks for playing!!" << endl;	
	return 0;


}

/***
 * Function: restart
 * Description: This function will select a new row/col/bom to restart
 * Parameters: row,col,bom
 * Pre-Conditions: 
 * Post-Conditions: the row,col, and bomb are changed
 **/

void restart(int *row, int *col, int *bom){
	int start = 1;
	while(start==1){
		cout << "Enter rows:" << endl;
		*row = test_string();
		cout << "Enter colums:" << endl;
		*col = test_string();
		cout << "Enter bombs:" << endl;
		*bom = test_string();
		if(*bom>(*row)*(*col)){
			cout << "More bombs then spaces!" << endl;
		}
		else{
			start = 0;
		}	
	}
}

/***
 * Function: playgame
 * Description: this function will help run the functions to get the game going
 * Parameters: the board, the row/col/bom
 * Pre-Conditions: valid board, row/col/bom
 * Post-Conditions: 
 **/

void playgame(char **board, int row, int col, int bom){
	int i, j, cor = 0, wro = 0;	
	char** gameboard = new char*[row];
	for(i=0; i<row; ++i)
		gameboard[i] = new char[col];
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			gameboard[i][j] = '-';
		}
	}
	while((cor<(bom)) || wro>0){
		pickchoice(gameboard, board, row, col, &cor, &wro);	
		if(cor==-1){
			cout << "Game Over" << endl;
			for(i=0; i<row; ++i){
				delete gameboard[i];
			}
			delete gameboard;
			for(i=0; i<row; ++i){
				delete board[i];
			}
			delete board;
			break;
		}
		if((cor==bom) && (wro==0)){
			cout << "YOU WIN!" << endl;
			for(i=0; i<row; ++i){
				delete gameboard[i];
			}
			delete gameboard;
			for(i=0; i<row; ++i){
				delete board[i];
			}
			delete board;
			break;
		}
	}
}

/***
 * Function: pickchoice
 * Description: this function allows the user to pick if they want to open a cell of do a flag
 * Parameters: the boards, the row/col, and correct/wrong value
 * Pre-Conditions: 
 * Post-Conditions: 
 **/
	
void pickchoice(char **gameboard, char **board, int row, int col, int *cor, int *wro){
	int choice, vr, vc;
	print(gameboard, row, col);
	cout << "1) reveal a spot\n2) place/remove a flag" << endl;
	choice = player_num();
	if(choice==1){
		checkpoint(&vr, &vc, row, col);
		checknum(gameboard, board, vr, vc, &cor, row, col);
	}
	if(choice==2){
		checkpoint(&vr, &vc, row, col);
		checkflag(gameboard, board, vr, vc, &cor, &wro, row, col); 
	}

}

/***
 * Function: checkflag
 * Description: this function will take a cell and convert it to a flag/remove the flag
 * Parameters: the boards, and a valid (vr, vc) point, the correct value and the wrong value
 * Pre-Conditions: valid board, valid point
 * Post-Conditions: the board will change one cell's flag status, and will edit the cor and wro value
 **/

void checkflag(char **gameboard, char **board, int vr, int vc, int **cor, int **wro, int row, int col){
	int start = 1;
	if(gameboard[vr][vc]=='-'){
		start = 0;
		gameboard[vr][vc] = '*';
		if(board[vr][vc]=='b'){
			**cor = **cor+1;
		}else{
			**wro = **wro+1;
		}
	}
	if(start == 1){ 
		if(gameboard[vr][vc]=='*'){
			gameboard[vr][vc] = '-';
			if(board[vr][vc]=='b'){
				**cor = **cor-1;
			}else{
				**wro = **wro-1;
			}
		}
	}
}

/***
 * Function: checkpoint
 * Description: This function will check if the point selected is a valid point
 * Parameters: rows and colums
 * Pre-Conditions: the rows and col
 * Post-Conditions: change te value of vr and vc to the valid point
 **/

void checkpoint(int *vr, int *vc, int row, int col){
	int start = 0;
	cout << "Row: ";
	while(start==0){
		*vr = test_string();
		if(*vr>=0 && *vr<row){
			start = 1;
		}
	}
	start = 0;
	cout << "Col: ";
	while(start==0){
		*vc = test_string();
		if(*vc>=0 && *vr<col){
			start = 1;
		}
	}
}

/***
 * Function: checknum
 * Description: this function is usesd to open cells
 * Parameters: the boards, the point needed to check (vr, vc), the rows and col
 * Pre-Conditions: the point is valid, valid boards
 * Post-Conditions: the board will edit depending on the cell opend, if its a bomb, it will set cor to -1
 **/

void checknum(char **gameboard, char **board, int vr, int vc, int **cor, int row, int col){
	int k, l;
	if(board[vr][vc] != '0' && board[vr][vc] != 'b' && gameboard[vr][vc] != '*'){
		gameboard[vr][vc] = board[vr][vc];
		**cor++;
	}
	if(board[vr][vc] == 'b' && gameboard[vr][vc]!='*'){
		cout << "BOOM" << endl;
		cout << "The game board" << endl;
		print(board, row, col);
		**cor = -1;
	}
	if(board[vr][vc] == '0'){
		gameboard[vr][vc]== '0';			
		for(k=-1;k<2;k++){
			for(l=-1;l<2;l++){
				if(vr-k >= 0 && vr-k <= row-1 && vc-l >= 0 && vc-1 <= col-1){
					if(board[vr-k][vc-l]== '0' && gameboard[vr-k][vc-l]!= '0'){
						reczero(gameboard, board, vr-k, vc-l, row, col);
					}
					gameboard[vr-k][vc-l] = board[vr-k][vc-l];
				}
					
			}
		}
	}
	if(gameboard[vr][vc]=='*'){
		cout << "Flag Warning" << endl;
	}
}


/***
 * Function: reczero
 * Description: This function is called to recursivly find 0's and open all cells around 0
 * Parameters: cell location, the boards
 * Pre-Conditions: the gameboard is valid
 * Post-Conditions: the gameboard will be edited to open the cells
 **/

void reczero(char **gameboard, char **board, int vr, int vc, int row, int col){
	int k, l;
	if(board[vr][vc] == '0'){
		gameboard[vr][vc] = '0';	
		for(k=-1;k<2;k++){
			for(l=-1;l<2;l++){
				if(vr-k >= 0 && vr-k <= row-1 && vc-l >= 0 && vc-1 <= col-1){
					if(board[vr-k][vc-l] == '0' && gameboard[vr-k][vc-l]!= '0'){
						reczero(gameboard, board, vr-k, vc-l, row, col);
					}
					gameboard[vr-k][vc-l] = board[vr-k][vc-l];
				}	
			}
		}
	}
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
		cout << "Bad Peramiters\n Please enter in the format of minesweeper -r # -c # -b #" << endl;
		cout << "Peramiter order doesn't matter, but they need to be in pairs (-c # -b # -r # is valid)" << endl;
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
	if(*bom>(*row)*(*col)){
		cout << "More bombs then spaces!" << endl;
		return 1;
	}
	if(value==3 && a == 1 && b == 1 && c == 1){
		return 0;
	}else{
		cout << "Bad Peramiters\n Please enter in the format of minesweeper -r # -c # -b #" << endl;
		cout << "Peramiter order doesn't matter, but they need to be in pairs (-c # -b # -r # is valid)" << endl;
		return 1;
	}
}


/***
 * Function: test_string
 * Description: This asks for user input and tests if it is a valid intiger between 1-9
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: The function outputs an integer between 1-9
 **/
int test_string(){
	int i, test, valuef;
	bool start;
	test = 0;
	start = true;
	string value;
	while(start==true){
		test = 0;
		cin >> value;
		for(int i = 0; i< value.size(); i++){
			if(value[i]<=57 && value[i]>=48){
				test += 1;
			}
			else{
				cout << "invalid input" << endl;
				cout << "New input: ";
			}
			if(test==value.size()){
				start = false;
			}
		}
	}
	valuef = atoi(value.c_str());
	return valuef;
}





//Format for functions
/***
 * Function: 
 * Description: 
 * Parameters: 
 * Pre-Conditions: 
 * Post-Conditions: 
 **/
