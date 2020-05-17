/**********
 * Program: set_up.cpp
 * Author: Trent Vasquez
 * Date: 6/5/2016
 * Description: This program generates test lists for the final
**********/

//***NOTE***
//This file is ment to acompony the final to generate  test lists
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
	cout << "The random filename ";
	cin >> cur_file;
	ofstream myfile (cur_file);	
	if(myfile.is_open()){
		for(int i = 0; i < num; i++){
			temp = rand() %1000;
			myfile << temp;
			myfile << " ";
		}
	}
	myfile.close();	
/*
	cout << "The best filename ";
	cin >> cur_file;
	myfile.open (cur_file);	
	if(myfile.is_open()){
		for(int i = 0; i < num; i++){
			myfile << i;
			myfile << " ";
		}
	}
	myfile.close();	

	cout << "The worst filename ";
	cin >> cur_file;
	myfile.open (cur_file);	
	if(myfile.is_open()){
		for(int i = num; i > 0; i--){
			myfile << i;
			myfile << " ";
		}
	}
	myfile.close();	

*/
	return 0;
}
