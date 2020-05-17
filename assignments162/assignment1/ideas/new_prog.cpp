/***
 *Program Filename:state_assignment.cpp
 *Author: Trent Vasquez
 *Date: 04/xx/2016
 *Description: This program can read into a file and help interpret state information
 **/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

const int DESC_SIZE = 30;

//Prototypes
int test_command(int, char*[], int*, char**);
int test_for_int();
void create_states(int, char**);
void read_file(char**);
struct coutny create_county();

struct county{
	string county;
	string *city;
	int cities;
	int population;
	float avg_income;
	float avg_house;
};

struct state{
	char name[DESC_SIZE];
	struct county *c;
	int counties;
	int population;
};

int main(int argc, char *argv[]){
	int valid = 1, state, temp;
	char *file_name;
	valid = test_command(argc, argv, &state, &file_name);
	if(valid == 1){
		return 1;
	}
	cout << sizeof(struct state) << endl;
	cout << sizeof(struct county) << endl;
	cout << sizeof(string) << endl;
	return 0;
}





/***
 * Function: int test_for_int
 * Description: This function takes user input and returns it as a integer, if invalid, will reprompt
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: Will return an integer
 **/
int test_for_int(){
	int i, test, valuef;
	bool start = true;
	test = 0;
	string value;
	while(start==true){
		test = 0;
		cin >> value;
		for(int i = 0; i < value.size(); i++){
			if(value[i]<=57 && value [i]>=48){
				test += 1;
			}else{
				cout << "Invalid input\nNew input: ";
			}
			if(test==value.size()){
				start = false;
			}
		}
	}
	valuef = atoi(value.c_str());
	return valuef;
}

/***
 * Function: int test_command
 * Description: this is used to find if the initial peramiters are valid when the function is called
 * Parameters: argc, argv, state, filename
 * Pre-Conditions: 
 * Post-Conditions: 1 is passed out if invalid input, 0 if correct
 **/
int test_command(int argc, char *argv[], int* state, char **file_name){
	int total=0;
	string message = "The program has failed to exicute. To correctly use this file, please make sure you enter: \nstate_assignment -s # -f \"filename\"\n";
	if(argc == 5){
		if(argv[1][0] == '-' && argv[1][1] == 's'){
			if(argv[3][0] == '-' && argv[3][1] == 'f'){
				*state = atoi(argv[2]);
				if(*state <= 0){
					cout << "You need a valid number of states" << endl;
					return 1;
				}
				*file_name = argv[4];
				ifstream input;
				input.open(*file_name);
				if(input.fail()){
					cout << "no file with this name" << endl;
					return 1;	
				}
				input.close();
			}else{
				cout << message;
				return 1;
			}
		}else{
			cout << message;
			return 1;
		}
	}else{
		cout << message;
		return 1;
	}
	return 0;
}











//Format for functions
/***
 * Function: 
 * Description: 
 * Parameters: 
 * Pre-Conditions: 
 * Post-Conditions: 
 **/
