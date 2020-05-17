/***
 *Program Filename: assignment4.cpp
 *Author: Trent Vasquez
 *Date: 2/11/2016
 *Description: This program will run a game of Wheel of Fortune
 **/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cctype>
#include <ctime>
#include <stdio.h>

using namespace std;

//Prototypes
void test_phrase(string *);
void mk_game_phrase(string, string *);
void give_points(int, int ***, int ***, int ***, int, int, int);
int player_num();
int spin();
int getletter(int *, string ***, string ***);	
void game_round(int, int *, int *, int *);
void turn_structure(int, int **, int **, int **, string *, string *);
void getvowl(string **, string **);
void round_score(int, int, int);
void total_scores(int **, int **, int **);
bool buyvowl(int, int *, int *, int *);
bool solve(string);
bool letter(string **, string **, int *, int *, int *, int);

int main(){
	int pnum, rounds, p1s, p2s, p3s;
	srand (time(0));
	cout << "Welcome to our game of wheel of fortune!" << endl;
	cout << "How many players will there be? (1-3) " << endl;

	pnum = player_num();

	cout << "How many game rounds will there be? (1-3) " << endl;
	rounds = player_num();
	while(rounds>0){ 
		game_round(pnum, &p1s, &p2s, &p3s);
		rounds = rounds - 1;
	}

	cout << "Thanks for playing!" << endl;
	return 0;
}

/***
 * Function: void game_round
 * Description: This will run each game round
 * Parameters: This functionw will edit pls, p2s, p3s at the end of the round
 * Pre-Conditions: None
 * Post-Conditions: None
 **/

void game_round(int pnum, int *p1s, int *p2s, int *p3s){
	string gphrase, sphrase;
	test_phrase(&sphrase);
	
	cout << "\n GPHRASE IS: " << sphrase << endl;
	mk_game_phrase(sphrase, &gphrase);
	//cout << string( 100, '\n' ); //Clears the screen
	cout << gphrase << endl;
	turn_structure(pnum, &p1s, &p2s, &p3s, &sphrase, &gphrase);
	total_scores(&p1s, &p2s, &p3s);
}

/***
 * Function: turn_structure
 * Description: When this is run, it will run the entire first round
 * Parameters: Number of players, the player scores
 * Pre-Conditions: None
 * Post-Conditions: The turn should execute and player scores should be changed
 **/

void turn_structure(int pnum, int **p1s, int **p2s, int **p3s, string *sphrase, string *gphrase){
	int cpnum, choice, p1cs, p2cs, p3cs;
	bool solved, turn;
	solved = false;
	cpnum = 0, p1cs = 0, p2cs = 0, p3cs = 0;
	do{
		if(cpnum==pnum){
			cpnum = 1;
		}else{
			++cpnum;
		}	
		turn = true;
		do{
			cout << cpnum << " player, it is your turn!" << endl;
			round_score(p1cs, p2cs, p3cs);
			cout << "Current Game Phrase: " << *gphrase << endl;
			cout << "Do you want to:\n1)Spin the wheel\n2)Buy a vowl\n3)Guess the solution" << endl;
			choice = player_num();
			if(choice==1){
				turn = letter(&sphrase, &gphrase, &p1cs, &p2cs, &p3cs, cpnum);
			}
			if(choice==2){
				if((buyvowl(cpnum, &p1cs, &p2cs, &p3cs) == true)){
					getvowl(&sphrase, &gphrase);
				}
			}
			if(choice==3){
				solved=solve(*sphrase);
				turn=false;
			}
		}
		while(turn==true);
		cout << string( 2, '\n') << endl;
	}	
	while(solved == false);	
	give_points(cpnum, &p1s, &p2s, &p3s, p1cs, p2cs, p3cs);
}


/***
 * Function: total_scores 
 * Description: Will display the overal scores for players
 * Parameters: The pointers to player scores
 * Pre-Conditions: 
 * Post-Conditions: 
 **/

void total_scores(int **p1s, int **p2s, int **p3s){	
	cout << "Our total round scores:" << endl;
	cout << "Player 1: " << **p1s << endl;
	cout << "Player 2: " << **p2s << endl;
	cout << "Player 3: " << **p3s << endl;
	cout << string( 2, '\n') << endl;

}

/***
 * Function: round_scores
 * Description: Shows the players current points for the round
 * Parameters: the player current scores
 * Pre-Conditions: 
 * Post-Conditions: 
 **/

void round_score(int p1cs, int p2cs, int p3cs){
	cout << "Our current round scores:" << endl;
	cout << "Player 1: " << p1cs << endl;
	cout << "Player 2: " << p2cs << endl;
	cout << "Player 3: " << p3cs << endl;
	cout << string( 2, '\n') << endl;


}

/***
 * Function: get letter
 * Description: This function will  allow the user to choose a letter to solve for in the puzzle
 * Parameters: the two phrase strings, the spin
 * Pre-Conditions: The two strings, what the user spun in the prior function
 * Post-Conditions: retunr the money the player earns
 **/

int getletter(int *s, string ***sphrase, string ***gphrase){	
	string letter, sp, gp;
	char let;
	sp = ***sphrase;
	gp = ***gphrase;
	int i, amo;
	amo = 0;
	cout << "You spun: " << *s << endl;
	cout << "What letter would you like to choose?" << endl;
	cout << "If you do not enter a lower case letter, you will waste your turn and recive no money" << endl;
	cin.ignore();
	getline(cin, letter);
	let = letter.at(0);
	if((let!=97)&&(let!=101)&&(let!=105)&&(let!=111)&&(let!=117)){
		for(i = 0; i<sp.size(); i++){
			if(sp.at(i)==let){
				if(gp.at(i)==45){
					gp.at(i)=let;
					amo++;
				}
			}
		}
	}
	***gphrase = gp;
	cout << ***gphrase << endl;
	cout << string( 2, '\n') << endl;
	return (amo)*(*s);
}





/***
 * Function: letter
 * Description: This is the first function that determins the resualt of the spin and then takes the player to choose a letter if they spin a good number
 * Parameters: the two phrases, and the current player round scores
 * Pre-Conditions: The game phrase should still have something to solve for
 * Post-Conditions: This funciton will return  a true statement if the player got a letter correct, it will return false if the player lost their turn
 **/
bool letter(string **sphrase, string **gphrase, int *p1cs, int *p2cs, int *p3cs, int cpnum){
	int s, mon;
	s = spin();
	if(s == 0){
		cout << "BANKRUPT!" << endl;
		if(cpnum==1){
			*p1cs = 0;
		}
		if(cpnum==2){
			*p2cs = 0;
		}
		if(cpnum==3){
			*p3cs = 0;
		}
		return false;		
	}
	if(s == 21){
		cout << "Skip turn :(" << endl;
		return false;
	}
	mon = getletter(&s, &sphrase, &gphrase);
	if(mon > 0){
		if(cpnum==1){
			*p1cs = *p1cs + mon;
		}
		if(cpnum==2){
			*p2cs = *p2cs + mon;
		}
		if(cpnum==3){
			*p3cs = *p3cs + mon;
		}
	
	}else{
		return false;
	}
}	

/***
 * Function: getvowl
 * Description: This function will allow the user to chose a vowl after they've spent 10 dollars
 * Parameters: the two strings
 * Pre-Conditions: 
 * Post-Conditions: The string should be modified if the player chose a vowl that was avalible
 **/

void getvowl(string **sphrase, string **gphrase){
	string vowl, sp, gp;
	sp = **sphrase;
	gp = **gphrase;
	int i;
	cout << "What vowl would you like to choose?" << endl;
	cout << "If you do not enter a lower case vowl, you will lose your money" << endl;
	cin.ignore();
	getline(cin, vowl);
	if(vowl.at(0)=='a'){
		for(i = 0; i<sp.size(); i++){
			if(sp.at(i)=='a'){
				gp.at(i)='a';
			}
		}
	}
	if(vowl.at(0)=='e'){
		for(i = 0; i<sp.size(); i++){
			if(sp.at(i)=='e'){
				gp.at(i)='e';
			}
		}
	}
	if(vowl.at(0)=='i'){
		for(i = 0; i<sp.size(); i++){
			if(sp.at(i)=='i'){
				gp.at(i)='i';
			}
		}
	}
	if(vowl.at(0)=='o'){
		for(i = 0; i<sp.size(); i++){
			if(sp.at(i)=='o'){
				gp.at(i)='o';
			}
		}
	}
	if(vowl.at(0)=='u'){
		for(i = 0; i<sp.size(); i++){
			if(sp.at(i)=='u'){
				gp.at(i)='u';
			}
		}
	}
	**gphrase = gp;
	cout << **gphrase << endl;
}

/***
 * Function: buy vowl
 * Description: This function checks if the user has enough points to buy a vowl
 * Parameters: The current player num and the current player scores
 * Pre-Conditions: 
 * Post-Conditions: if the current user has enough points, it will sub 10 from thier current score and return true, else return false
 **/

bool buyvowl(int cpnum, int *p1cs, int *p2cs, int *p3cs){
	if(cpnum==1){
		if(*p1cs>=10){
			*p1cs = *p1cs-10;
			return true;
		}
	}
	if(cpnum==2){
		if(*p2cs>=10){
			*p2cs = *p2cs-10;
			return true;
		}
	}
	if(cpnum==3){
		if(*p3cs>=10){
			*p3cs = *p3cs-10;
			return true;
		}
	}
	return false;
}

/***
 * Function: give_points 
 * Description:  saves the players points for their final score
 * Parameters: current scores, current player
 * Pre-Conditions: the puzzle was just solved, player num is between 1-3
 * Post-Conditions: the player score will be saved to a pointer variable
 **/

void give_points(int cpnum, int ***p1s, int ***p2s, int ***p3s, int p1cs, int p2cs, int p3cs){
	if(cpnum==1){
		***p1s += p1cs;
	}
	if(cpnum==2){
		***p2s += p2cs;
	}
	if(cpnum==3){
		***p3s += p3cs;
	}
}

/***
 * Function: solve
 * Description: Allows the player a chance to solve the puzzle
 * Parameters: The puzzle
 * Pre-Conditions: There is a puzzle to solve
 * Post-Conditions: The players score will be added to their total
 **/

bool solve(string sphrase){
	string value;
	int i;
	cout << "Enter the secret phrase:" << endl;
	cin.ignore();
	getline(cin, value);
	for(int i = 0; i < value.size(); i++){
		if(value[i]<=90 && value [i]>=65){
			value[i] = value[i]+32;
		}
	}
	if(value == sphrase){
		cout << "True" << endl;
		return true;
	}else{
		cout << "False" << endl;
		return false;
	}
}

/***
 * Function: spin
 * Description: Will find a number between 0 and 21
 * Parameters: 
 * Pre-Conditions: 
 * Post-Conditions: will return a number between 0 and 21 as an integer
 **/

int spin(){
	int num;
	num = rand() % 22;
	cout << num << endl;
	return num;
}

/***
 * Function: test_phrase
 * Description: This asks for user input to find a valid string containing  a-z
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: The function outputs a string wiht letters  between a-z
 **/
void test_phrase(string *str){
	int i, test, start;
	start = 1;
	string value;
	while(start==1){
		cout << "Enter the secret phrase: " << endl;
		cin.ignore();
		test = 0;
		i = 0;
		getline(cin, value);
		for(int i = 0; i < value.size(); ++i){
			if((value[i]<=122 && value[i]>=97)||(value[i]==32)){
				test += 1;
			}
			else{
				if(value[i]<=90 && value [i]>=65){
					value[i] = value[i]+32; //converts upercase to lowercase
					test += 1;
				}else{
					cout << "invalid input" << endl;
				}
			}
			if(test==value.size()){
				start = 0;
			}
		}
	}
	*str = value;
}

/***
 * Function: make_game_phrase
 * Description: makes a copy of the main phrase, and converts it to what the players will see
 * Parameters: A valid phrase
 * Pre-Conditions: The phrase is valid
 * Post-Conditions: The function will RETURN a string consisting of all "-"
 **/

void mk_game_phrase(string str, string *nstr){
	int i;
	for(int i = 0; i < str.size(); i++){
		if(str[i] != 32){
			str[i] = 45;
		}	
	}
	*nstr = str;
}


/***
 * Function: player_num
 * Description: Asks the user for a number of players between 1-3
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: The user will be able to choose a value between 1-3
 **/

int player_num(){
	int start, valuef;
	string num;
	start = 1;
	while(start==1){
		cin >> num;
		if(num=="1" || num=="2" || num=="3"){
			valuef = atoi(num.c_str());
			return valuef;
		}else{
			cout << "Invalid input, New input: ";
		}
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
