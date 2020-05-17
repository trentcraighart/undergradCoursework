#include "functions.h"

/***
 * Function: buy_animal
 * Description: Allows the user to buy an animal if they have enough money
 * Parameters: the zoo used for the game
 * Pre_Conditions: none
 * Post_Conditions: the animal arrays might change
***/

void buy_animal(Zoo *game){
	Tiger b_tiger(3);
	Bear b_bear(3);
	Penguine b_penguine(3);
	int start = 1, cho, cur_mon, temp;
	while(start == 1){
		cur_mon = game->cur_money();
		cout << "Current money: " << cur_mon << endl;
		cout << "What animal do you want to buy?\n1)Tiger 2)Bear 3)Penguine 4)None" << endl;
		cho = get_int();
		switch(cho){
			case 1:
				if(game->cur_money() >= 10000){
					game->sub_money(10000);
					game->add_tiger_arr(b_tiger);	
				}else{
					cout << "Not enough money" << endl;
				}
				break;
			case 2:
				if(game->cur_money() >= 5000){
					game->sub_money(5000);
					game->add_bear_arr(b_bear);	
				}else{
					cout << "Not enough money" << endl;
				}
				break;
			case 3:
				if(game->cur_money() >= 1000){
					game->sub_money(1000);
					game->add_penguine_arr(b_penguine);	
				}else{
					cout << "Not enough money" << endl;
				}
				break;
			case 4:
				start = 0;
				break;
			default:
				cout << "Invalid choice" << endl;
		}
	}
}

/***
 * Function: get_int
 * Description: This function takes in a valid int from user
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: will return an int
***/


int get_int(){
	int i, valuef, test = 0, start = 1;
	string value;
	while(start == 1){
		test = 0;
		cin >> value;
		for(int i = 0; i < value.size(); i++){
			if(value[i]<=57 && value[i]>=48){
				test += 1;
			}else{
				cout << "invalid input, new input:";
			}
			if(test==value.size()){
				start = 0;
			}
		}
	}
	valuef = atoi(value.c_str());
	return valuef;
}

//Template
/***
 * Function:
 * Description:
 * Parameters:
 * Pre_Conditions:
 * Post_Conditions:
***/
