/***
 *Program Filename: assignment3.cpp
 *Author: Trent Vasquez
 *Date: 1/30/2016
 *Description: This a program that makes a grid, takes user input on points, and draws a line between them
 *Input: The users points
 *Output: The program should output the grid with two points connected by lines
 **/


#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

/***
 *Function: find_path
 *Description: Will find a path from the start point to the end point by printing each piece of the grid 
 *Parameters: xst, yst, xen, yen, dash, fbox, ebox
 *NOTE dash, fbox, and ebox are just strings that I'm using for the grid, they are not input
 *Return: None
 *Pre-Conditions: all parameters are valid integers
 *Post-Conditions: the path will be printed on the screen, xst==xen, and yst==yen
 **/
void find_path(int xst, int yst, int xen, int yen, string dash, string fbox, string ebox){
	int xy11, xy12, xy13, xy14, xy21, xy22, xy23, xy24, xy31, xy32, xy33, xy34, xy41, xy42, xy43, xy44;
	xy11 = 0, xy12 = 0, xy13 = 0, xy14 = 0, xy21 = 0, xy22 = 0, xy23 = 0, xy24 = 0;
	xy31 = 0, xy32 = 0, xy33 = 0, xy34 = 0, xy41 = 0, xy42 = 0, xy43 = 0, xy44 = 0;

	if(xst==1 && yst==1){
		xy11 = 1;
	}
	if(xst==1 && yst==2){
		xy12 = 1;
	}
	if(xst==1 && yst==3){
		xy13 = 1;
	}
	if(xst==1 && yst==4){
		xy14 = 1;
	}
	if(xst==2 && yst==1){
		xy21 = 1;
	}
	if(xst==2 && yst==2){
		xy22 = 1;
	}
	if(xst==2 && yst==3){
		xy23 = 1;
	}
	if(xst==2 && yst==4){
		xy24 = 1;
	}
	if(xst==3 && yst==1){
		xy31 = 1;
	}
	if(xst==3 && yst==2){
		xy32 = 1;
	}
	if(xst==3 && yst==3){
		xy33 = 1;
	}
	if(xst==3 && yst==4){
		xy34 = 1;
	}
	if(xst==4 && yst==1){
		xy41 = 1;
	}
	if(xst==4 && yst==2){
		xy42 = 1;
	}
	if(xst==4 && yst==3){
		xy43 = 1;
	}
	if(xst==4 && yst==4){
		xy44 = 1;
	}
	
	while (xst!=xen || yst!=yen){
		//This block is looking for the next point to set to true
		if(xst!=xen){
			if(xst>xen){
				xst = xst-1;
			}else{
				xst = xst+1;
			}	
		}else{
			if(yst>yen){
				yst = yst-1;
			}else{
				yst = yst+1;
			}
		}	
		if(xst==1 && yst==1){
			xy11 = 1;
		}
		if(xst==1 && yst==2){
			xy12 = 1;
		}
		if(xst==1 && yst==3){
			xy13 = 1;
		}
		if(xst==1 && yst==4){
			xy14 = 1;
		}
		if(xst==2 && yst==1){
			xy21 = 1;
		}
		if(xst==2 && yst==2){
			xy22 = 1;
		}
		if(xst==2 && yst==3){
			xy23 = 1;
		}
		if(xst==2 && yst==4){
			xy24 = 1;
		}
		if(xst==3 && yst==1){
			xy31 = 1;
		}
		if(xst==3 && yst==2){
			xy32 = 1;
		}
		if(xst==3 && yst==3){
			xy33 = 1;
		}
		if(xst==3 && yst==4){
			xy34 = 1;
		}
		if(xst==4 && yst==1){
			xy41 = 1;
		}
		if(xst==4 && yst==2){
			xy42 = 1;
		}
		if(xst==4 && yst==3){
			xy43 = 1;
		}
		if(xst==4 && yst==4){
			xy44 = 1;
		}
		//Below here is where we are going to print the grid

		cout << dash << endl;
		if(xy11==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy12==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy13==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy14==0){
			cout << ebox << endl;
		}else{
			cout << fbox << endl;
		}
		cout << dash << endl;
		if(xy21==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy22==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy23==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy24==0){
			cout << ebox << endl;
		}else{
			cout << fbox << endl;
		}	
		cout << dash << endl;
		if(xy31==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy32==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy33==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy34==0){
			cout << ebox << endl;
		}else{
			cout << fbox << endl;
		}
		cout << dash << endl;
		if(xy41==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy42==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy43==0){
			cout << ebox;
		}else{
			cout << fbox;
		}
		if(xy44==0){
			cout << ebox << endl;
		}else{
			cout << fbox << endl;
		}
		cout << dash << endl;
	}	
}
/***
 * Function: test_string
 * Description: This asks for user input and tests if it is a valid intiger between 1-4
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: The function outputs an integer between 1-4
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
			if(value[i]<=52 && value[i]>=49){
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

int main(){
	int xst, yst, xen, yen, run;
	run = 0, xst = 0, yst = 0, xen = 0, yen= 0;
	string dash, fbox, ebox;
	//Here are some strings I will be using to generate the visual
	dash = "------------";
	fbox = "|X|";
	ebox = "| |";
	//Asking for user input
	cout << "X starting point ";
	xst = test_string();	
	cout << "Y starting point ";
	yst = test_string();
	cout << "X ending point ";
	xen = test_string();
	cout << "Y ending point ";
	yen = test_string();
	
	find_path(xst, yst, xen, yen, dash, fbox, ebox);	

	cout << "Do you want to run the program again? (1=yes) ";
	cin >> run;
	if(run==1){
		main();
	}
}

