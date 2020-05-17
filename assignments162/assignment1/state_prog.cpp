#include "state_prog.h"

/***
 * Function: function_menu
 * Description: This function facilitates the use of other functions for the user
 * Parameters: the list struct, number of states currently, and the file name being used
 * Pre-Conditions: none
 * Post-Conditions: none
 **/

void function_menu(struct state * list, int num, char **file_name){
	int choice;
	char temp[50];
	do{
	cout << "1) New state document\n2) States by population\n3) States by name\n4) Largest County\n5) Counties above X average income" << endl;
	cout << "6) Average house values\n7) Exit the program" << endl;
	cout << "Chose your operation: ";
	choice = test_for_int();
	switch(choice){
			case 1: delete_memory(list, num);
				cout << "Name of the new states txt file: ";
				cin.clear();
				cin.ignore();
				cin.getline(*file_name, 50, '\n');
				cout << "Number of states: ";
				num = test_for_int();
				list = create_states(num, file_name);
				break;
			case 2: large_state(list, num);
				break;
			case 3: state_by_name(list, num);
				break;
			case 4: largest_county(list, num);
				break;
			case 5: counties_above(list, num);
				break;
			case 6: average_house(list, num);
				break;
			case 7: cout << "Thanks for using the state program!" << endl;
				break;
			default: cout << "improper number" << endl;
	
		}
	}while(choice != 7);
	delete_memory(list, num);
}


/***
 * Function: average_house
 * Description: adds all the house values in the stated and averages them
 * Parameters: list and num of states
 * Pre-Conditions: none
 * Post-Conditions: none
 **/

void average_house(struct state * list, int num){
	int i, j, k, amo = 0, tot = 0;
	for(i=0;i<num;i++){
		amo = 0;
		tot = 0;
		k = list[i].counties;
		for(j=0;j<k;j++){
			amo = amo + list[i].c[j].avg_house;
		}
		tot = amo/k;
		cout << list[i].name << ": " << tot << endl;
	}
}


/***
 * Function: counties_above
 * Description: lists all counties above x amount
 * Parameters: list and num of states
 * Pre-Conditions: none
 * Post-Conditions: none
 **/
void counties_above(struct state * list, int num){
	int amo, i, j, k;
	cout << "Specific quantity: " << endl;
	amo = test_for_int();
	for(i=0;i<num;i++){
		k = list[i].counties;
		for(j=0;j<k;j++){
			if(list[i].c[j].avg_income >= amo){
				cout << list[i].c[j].county << endl;
			}
		}		
	}
}

/***
 * Function: largest_county
 * Description: list the largest county by population
 * Parameters: the list and state num
 * Pre-Conditions: none
 * Post-Conditions: none
 **/

void largest_county(struct state * list, int num){
	struct county temp;
	temp.population = 0;
	temp.county = "name";
	int i, k, j;
	for(i=0;i<num;i++){
		k = list[i].counties;
		for(j=0;j<k+1;j++){
			if(list[i].c[j].population > temp.population){
				temp.population = list[i].c[j].population;
				temp.county = list[i].c[j].county;
			}	
		}
	}
	cout << "Name: " << temp.county << " Population: " << temp.population << endl;
}

/***
 * Function: state_by_name
 * Description: lists all states by alphabetical name
 * Parameters: list and num of states
 * Pre-Conditions: 
 * Post-Conditions: 
 **/

void state_by_name(struct state * list, int num){
	struct state * temp;
	struct state * seclist;
	int i, j;
	temp = new struct state[num];
	seclist = new struct state[num];
	for(i=0;i<num;i++){
		temp[i] = list[i];
		seclist[i] = list[i];
	}
	for(j=0;j<num-1;j++){
		for(i=0;i<num-1;i++){
			if(seclist[i].name > seclist[i+1].name){
				temp[i] = seclist[i+1];
				seclist[i+1] = seclist[i];
				seclist[i] = temp[i];
			}
		}
	}
	for(i=0;i<num;i++){
		cout << i+1 << " " << seclist[i].name << " " << seclist[i].population << endl;
	}
	delete [] temp;
	delete [] seclist;
}



/***
 * Function: large_state
 * Description: takes the list and finds out which one has the highest population
 * Parameters: list and number of states
 * Pre-Conditions: the list and num correspond correctly
 * Post-Conditions: none
 **/

void large_state(struct state * list, int num){
	struct state * temp;
	struct state * seclist;
	int i, j;
	temp = new struct state[num];
	seclist = new struct state[num];
	for(i=0;i<num;i++){
		temp[i] = list[i];
		seclist[i] = list[i];
	}
	for(j=0;j<num-1;j++){
		for(i=0;i<num-1;i++){
			if(seclist[i].population < seclist[i+1].population){
				temp[i] = seclist[i+1];
				seclist[i+1] = seclist[i];
				seclist[i] = temp[i];
			}
		}
	}
	for(i=0;i<num;i++){
		cout << i+1 << " " << seclist[i].name << " " << seclist[i].population << endl;
	}
	delete [] temp;
	delete [] seclist;
}

/***
 * Function: delete_memory
 * Description: This function takes the list of all the states and delets the dynamic memory
 * Parameters: the list of states, the number of states
 * Pre-Conditions: the number of states exist, the state list is correct
 * Post-Conditions: nothing
 **/
void delete_memory(struct state * list, int num){
	int i, j, k, l = 0, county, citiesi, candy;
	for(i=0; i<num; i++){
		for(j=0;j<list[i].counties;j++){
			l++;
			delete [] list[i].c[j].city;
		}
		delete [] list[i].c;
	}
	delete [] list;
}

/***
 * Function: create_states 
 * Description: This function reads the file supplied by the user and loads them into the program
 * Parameters: the number of states, the file name
 * Pre-Conditions: the file be correctly formated, less num then states on file
 * Post-Conditions: return a dynamic 1d array of states
 **/

struct state * create_states(int num, char **file_name){
	string line, temp;
	char *c_string;
	int state = 3, county = 0, totcounty = 0, totstate = 0, tempint, index, curcounty, city;
	struct state *list = new struct state [num];
	ifstream myfile(*file_name);
	while(getline(myfile,line)){
		if(totstate<num){
			if(state==3){
				int i = 0;
				while(state == 3){
					if(line.at(i) == ' '){
						list[totstate].name = line.substr(0,i);
						state = 2;
					}else{
						i++;
					}	
				}	
				int j = i+1;
				while(state == 2){
					if(line.at(j) == ' '){
						temp = line.substr(i,j);
						c_string = new char[temp.length()];
						for(index = 0; index<temp.length(); index++){
							c_string[index] = temp[index];
						}
						tempint = atoi(c_string);
						list[totstate].population = tempint;
						state = 1;
						delete c_string;
					}else{
						j++;
					}
				}
				int k = j+1;
				while(state == 1){
					temp = line.substr(j,k);	
					c_string = new char[temp.length()];
					for(index = 0; index<temp.length(); index++){
						c_string[index] = temp[index];
					}
					tempint = atoi(c_string);
					list[totstate].counties = tempint;
					state = 0;
					delete c_string;
					list[totstate].c = new struct county[list[totstate].counties];
					totcounty = list[totstate].counties;
					if(totcounty == 0){
						totstate++;
						state = 3;
					}
				}
			}else{
				totcounty--;
				county = 5;
				int i = 0;
				while(county == 5){
					if(line.at(i) == ' '){
						list[totstate].c[totcounty].county = line.substr(0,i);
						county = 4;
					}else{
						i++;
					}
				}
				int j = i+1;
				while(county == 4){
					if(line.at(j) == ' '){
						temp = line.substr(i,j);
						c_string = new char[temp.length()];
						for(index = 0; index<temp.length(); index++){
							c_string[index] = temp[index];
						}
						tempint = atoi(c_string);
						list[totstate].c[totcounty].population = tempint;
						county = 3;
						delete c_string;
					}else{
						j++;
					}
				}
				int k = j+1;
				while(county == 3){
					if(line.at(k) == ' '){	
						temp = line.substr(j, k);
						c_string = new char[temp.length()];
						for(index = 0; index<temp.length(); index++){
							c_string[index] = temp[index];
						}
						tempint = atoi(c_string);
						list[totstate].c[totcounty].avg_income = tempint;
						county = 2;
						delete c_string;
					}else{
						k++;
					}
				}
				int l = k+1;
				while(county == 2){
					if(line.at(l) == ' '){
						temp = line.substr(k, l);
						c_string = new char[temp.length()];
						for(index = 0; index<temp.length(); index++){
							c_string[index] = temp[index];
						}
						tempint = atoi(c_string);
						list[totstate].c[totcounty].avg_house = tempint;
						county = 1;
						delete c_string;
					}else{
						l++;
					}
				}
				int m = l+1;
				while(county == 1){
					if(line.at(m) == ' '){
						temp = line.substr(l, m);	
						c_string = new char[temp.length()];
						for(index = 0; index<temp.length(); index++){
							c_string[index] = temp[index];
						}
						tempint = atoi(c_string);
						list[totstate].c[totcounty].cities = tempint;
						city = tempint;
						county = 0;
						delete c_string;
					}else{
						m++;
					}
				}	
				i = m+1;
				j = i+1;
				list[totstate].c[totcounty].city = new string[city];
				while(city>0){
					if(j == line.length()){
						list[totstate].c[totcounty].city[city-1] = line.substr(i,j-1);
						city--;
						i = j+1;
						j++;
						break;
					}
					if(line.at(j) == ' '){
						list[totstate].c[totcounty].city[city-1] = line.substr(i,j-i);
						i = j+1;
						j++;
						city--;
					}else{
						j++;
					}
				}
				if(totcounty == 0){
					state = 3;
					totstate++;
					
				}
			}	
		}else{
			return list;
		}
	}
	return list;
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
					exit(EXIT_FAILURE);
				}
				*file_name = argv[4];
				ifstream input;
				input.open(*file_name);
				if(input.fail()){
					cout << "no file with this name" << endl;
					exit(EXIT_FAILURE);
				}
				input.close();
			}else{
				cout << message;
				exit(EXIT_FAILURE);
			}
		}else{
			cout << message;
			exit(EXIT_FAILURE);
		}
	}else{
		cout << message;
		exit(EXIT_FAILURE);
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
