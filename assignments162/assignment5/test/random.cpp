/**********
 * Program: random.cpp
 * Author: Trent Vasquez
 * Date: 6/4/2016
 * Description: This program was made to output a variable amount of random numbers between 0-99 to a txt file
**********/

//***NOTE***
//This file is ment to acompony assignment 5 for generating random test lists
//**********

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

int main(){
	srand(time(NULL));
	char cur_file[20];
	int num, temp;

	cout << "how many numbers do you want in your file? ";
	cin >> num;
	cout << "What file do you want to use? ";
	cin >> cur_file;

	ofstream myfile (cur_file);
	
	if(myfile.is_open()){
		for(int i = 0; i < num; i++){
			temp = rand() %100;
			myfile << temp;
			myfile << " ";
		}
	}
	myfile.close();	

	return 0;
}
