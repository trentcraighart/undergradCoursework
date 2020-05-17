/***
 *Program Filename: assignment5.cpp
 *Author: Trent Vasquez
 *Date: 2/29/2016
 *Description: This program will translate morse code to english in vice versa
 **/
#include <iostream>
#include <cstring>
#include <cctype>
#include <stdlib.h>
#include <istream>

using namespace std;

//Prototypes
int choice();
void etom(string[27], char[27]);
void mtoe(string[27], char[27]);

int main(){
	char let[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
	string code[27] = {".-   ","-...   ","-.-.   ","-..   ",".   ","..-.   ","--.   ","....   ","..   ",".---   ","-.-   ",".-..   ","..   ","-.   ","---   ",".--.   ","--.-   ",".-.   ","...   ","-   ","..-   ","...-   ",".--   ","-..-   ","-.--   ","--..   ","    "};
	int start = 1, num;
	cout << "Welcome to the morse code translator!\nPress 1 for English to morse code\nPress 2 for morse code to English code" << endl;	
	num = choice();
	switch(num){
	case 1:
		etom(code, let);
		break;
	case 2:
		mtoe(code, let);
		break;
	}
}


/***
 * Function: void etom
 * Description: asks the user for a english phrase and outputs it to morse code
 * Parameters: The morse code array and the alphabet array
 * Pre-Conditions: none
 * Post-Conditions: none
 **/

void etom(string code[27], char let[27]){
	cout << "Enter the phrase you want converted" << endl;
	char * input;
	input = new char[0];
	int i, c, start, x = 0;
	cin.ignore();

	cin.get(input, 10000, '\n');	

	cout << input << endl;	
	for(i=0;i<strlen(input);i++){
		start = 1;
		c = 0;
		while(start==1){
			if(input[i]==let[c]){
				cout << code[c];
				start = 0;
			}else{
				c = c+1;
			}
			if(c>26){
				start = 0;
			}
		}
	}
}


/***
 * Function: void mtoe
 * Description: takes user input in morse code and displays it as english
 * Parameters: the morse code array and the alphabet array
 * Pre-Conditions: none
 * Post-Conditions: none
 **/

void mtoe(string code[27], char let[27]){
	const char * alph[27] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", " "};
	const char * morse[27] = {".-   ","-...   ","-.-.   ","-..   ",".   ","..-.   ","--.   ","....   ","..   ",".---   ","-.-   ",".-..   ","..   ","-.   ","---   ",".--.   ","--.-   ",".-.   ","...   ","-   ","..-   ","...-   ",".--   ","-..-   ","-.--   ","--..   ","    "};
	cout << "Enter the phrase you want converted" << endl;
	cout << "Note, 3 spaces after each leter, 7 after each word" << endl;
	char * input;
	char * nstring;
	input = new char[0];
	nstring = new char[0];
	char teststr[15] = "";
	int i, c, j, start, tot, nlet, fchar = 0, stot = 0, end = 0, cor = 1, cat;
	cin.ignore();
	cin.get(input, 10000, '\n');
	for(i=0; i<strlen(input); i++){
		if(fchar==0){
			if(input[i]==' '){
				stot = stot+1;
				if(stot==4){
					strcat(nstring, " ");
					stot = 0;
				}
			}else{
				stot = 0;
				fchar = 1;
			}
		}
		if(fchar==1){
			if(input[i]=='.'){
				strcat(teststr, ".");

			}else if(input[i]=='-'){
				strcat(teststr, "-");

			}else if(input[i]==' '){
				strcat(teststr, " ");
				end = end+1;
			}
			if(end==3){
				for(j=0;j<26;j++){
					cor = strcmp(morse[j], teststr);
					if(cor==0){
						strcat(nstring, alph[j]);
						cor = 1;
						fchar = 0;
						end =0;
						teststr[0] = '\0';
						break;
					}
				}
			}		
		}
	}
	cout << nstring << endl;
}



/***
 * Function: int choice()
 * Description: a function that makes the user pick a number betwwn 1 or 2
 * Parameters: 
 * Pre-Conditions: 
 * Post-Conditions: return 1 or 2 as an int
 **/

int choice(){
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

//Format for functions
/***
 * Function: 
 * Description: 
 * Parameters: 
 * Pre-Conditions: 
 * Post-Conditions: 
 **/
