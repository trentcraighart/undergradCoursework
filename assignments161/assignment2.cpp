/******
 * Program: assignment2.cpp
 * Author: Trent Vasquez
 * Date :1/16/2016
 * Description: It is a program designed to help you find a loan balance, continuously compun intrest, and future value 
 * Input: The users information
 * Output: The amount of money in relation to the function used
 * *****/

#include <iostream>
#include <cmath> 
using namespace std;
#define E 2.71828
string intrateexe("Example 9%, 9%/12 = 0.75% = 0.0075");

//This function is used to find the balance of a loan based of initial investment, rate of intrest, and time
//It also taes into account the users payments per period
int loanbalance(){
	double inv, invrat, pay, time, loan;
	cout << "You chose Loan Balance" << endl;
	cout << "What is the initial investment: " << endl;
	cin >> inv;
	cout << "What is the yearly intrest rate per period in a decimal: " << endl;
	cout << intrateexe << endl;
	cin >> invrat;
	cout << "How much are you paying per period: " << endl;
	cin >> pay;
	cout << "How many periods have elapsed: " << endl;
	cin >> time;
	loan = inv*(pow(1+invrat,time))-(pay/invrat)*((pow(1+invrat,time))-1);
	cout << "After " << time << " years, you will have " << loan << " left" << endl;
}

//This function solves for continous compound intrest using user inputs
//User inputs include principle, rate of anuual intrest, time in years
int contcompint(){
	double prin, anin, time, amou;
	cout << "You chose Continously Comounded Intrest" << endl;
	cout << "What is the principle investment: " << endl;
	cin >> prin;
	cout << "What is the annual intrest rate as a decimal: " << endl;
	cout << intrateexe << endl;
	cin >> anin;
	cout << "How many years: " << endl;
	cin >> time;
	amou = prin*(pow(E,anin*time));
	cout << "After " << time << " years, you will have " << amou <<  endl;
}

//This program will allow the user to calculate the future value based off of factors such as:
//Starting cash flow, rate of return, and the total amount of periods
int futurevalue(){
	double stca, rate, peri, fuva;
	cout << "You chose Future Value" << endl;
	cout << "What is the starting cash flow: " << endl;
	cin >> stca;
	cout << "What is the precent rate of return in a decimal : " << endl;
	cout << intrateexe << endl;
	cin >> rate;
	cout << "How many periods: " << endl;
	cin >> peri;
	fuva = stca*(pow(1+rate,peri));
	cout << "After " << peri << " periods, you will have " << fuva << endl;
}
		
int main(){
	int choice;

	cout << "Welcome to my finance calculator" << endl;
	cout << "1 - Loan Balance" << endl;
	cout << "2 - Continuously Compunt Intrest" << endl;
	cout << "3 - Future Value" << endl;
	
	cin >> choice;
	switch(choice){

	case 1:
		loanbalance();
		break;
	case 2:
		contcompint();	
		break;
	case 3:
		futurevalue();
		break;
	defualt:
		cout << "That is an invalid input, the program will now quit" << endl;
		break;
	return 0;
	}
}
