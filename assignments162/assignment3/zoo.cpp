#include "zoo.h"
#include "functions.h"
#include "animal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Zoo::Zoo(){
	food_cho = 0;
	money = 100000;
	food_price = 5;
	day = 0;
	num_tiger = 0;
	num_bear = 0;
	num_penguine = 0;
	num_animals = 0;
	tiger_arr = new Tiger[0];
	bear_arr = new Bear[0];
	penguine_arr = new Penguine[0];
}

Zoo::~Zoo(){
	delete [] tiger_arr;
	delete [] bear_arr;
	delete [] penguine_arr;
}

//BASIC ACCESORS AND MUTATORS

void Zoo::inc_day(){
	day++;
}

int Zoo::out_day(){
	return day;
}

int Zoo::cur_money(){
	return money;
}

void Zoo::sub_money(int ded){
	money = money - ded;
}

//FUNCTIONS

/***
 * Function: inc_age
 * Description: this function will increment age for all animals
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: none
***/

void Zoo::inc_age(){
	int i;
	for(i = 0; i < num_tiger; i++){
		tiger_arr[i].age_up();
	}
	for(i = 0; i < num_bear; i++){
		bear_arr[i].age_up();
	}
	for(i = 0; i < num_penguine; i++){
		penguine_arr[i].age_up();
	}
}

/***
 * Function: birth
 * Description: this function will check if there is an avalible animal to give birth
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: increases will add an animal randomly to one of the arrays
***/

void Zoo::birth(){
	Tiger tbaby(0);
	Bear bbaby(0);
	Penguine pbaby(0);

	int ta, ba, pa, tb = 0, bb = 0, pb = 0, ani, finding = 1;
	for(int i = 0; i < num_tiger; i++){
		ta = tiger_arr[i].get_age();
		if(ta >= 3){
			tb = 1;
			break;
		}
	}
	for(int i = 0; i < num_bear; i++){
		ba = bear_arr[i].get_age();
		if(ba >= 3){
			bb = 1;
			break;
		}
	}
	for(int i = 0; i < num_penguine; i++){
		pa = penguine_arr[i].get_age();
		if(pa >= 3){
			pb = 1;
			break;
		}
	}
	while(finding == 1){
		if(tb == 1 || bb == 1 || pb == 1){
			ani = rand() % 3;
			if(ani == 0){
				if(tb == 1){
					cout << "A tiger gave birth at the age of " << ta << endl;
					add_tiger_arr(tbaby);
					finding = 0;
				}else{
					ani++;
				}
			}
			if(ani == 1){
				if(bb == 1){
					cout << "A bear gave birth to twins at the age of " << ba << endl;
					add_bear_arr(bbaby);
					add_bear_arr(bbaby);
					finding = 0;
				}else{
					ani++;
				}
			}
			if(ani == 2){
				if(pb == 1){
					cout << "A penguine gave birth to triplets at the age of " << pa << endl;
					add_penguine_arr(pbaby);
					add_penguine_arr(pbaby);
					add_penguine_arr(pbaby);
					finding = 0;
				}else{
					ani = 0;
				}
			}
		}else{
			finding = 0;
			cout << "No valid animals to have a baby" << endl;
		}
	}
}

/***
 * Function: boom
 * Description: this function will increase the zoo's money
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: increases money randomly with tiger
***/

void Zoo::boom(){
	int amo, nmon;
	amo = rand() % 250 + 250;
	nmon = amo * num_tiger;
	cout << "Your tigers made you an additional " << nmon << endl;
}

/***
 * Function: animal_death();
 * Description: this function will kill a random animal
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: if there was an animal, it will be killed
***/

void Zoo::animal_death(){
	int animal, spot, age;
	if(num_animals > 0){
		animal = rand() % num_animals + 1;
		if(animal <= num_tiger){
			cout << "A tiger has died!" << endl;
			age = tiger_arr[animal].get_age();
//			cout << "The tiger died at the age of " << age << endl;
			rem_tiger_arr(animal);
		}else if(animal <= num_tiger + num_bear){
			spot = (animal - num_tiger);
			cout << "A bear has died!" << endl;
			age = bear_arr[spot].get_age();
//			cout << "The bear died at the age of " << age << endl;
			rem_bear_arr(spot);
		}else{
			spot = (animal - num_tiger - num_bear);
			cout << "A penguine has died!" << endl;
			age = penguine_arr[animal].get_age();
//			cout << "The penguine died at the age of " << age << endl;
			rem_penguine_arr(spot);
		}
	}else{
		cout << "There are no animals in your zoo to die" << endl;
	}
}

/***
 * Function: random_event()
 * Description: this function will call a random event
 * Parameters: none
 * Pre_Conditions: none
 * Post_Conditions: none
***/

void Zoo::random_event(){
	int event;
	num_animals = num_tiger + num_bear + num_penguine;
	event = rand() % (food_cho + 3);
	switch(event){
		case 1:
			cout << "\nNothing Happens this day\n" << endl;
			break;
		case 2:
			cout << "\nBoom in zoo attendence\n" << endl;
			boom();
			break;
		case 3:
			cout << "\nBaby animal is born\n" << endl;
			birth();
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			cout << "\nAn animal has died\n" << endl;
			animal_death();
			break;
		default:
			cout << "\nNothing Happens this day\n" << endl;
			break;	
	} 
}

/***
 * Function: profit_animals()
 * Description: this function will do get the money for the animals
 * Parameters: none
 * Pre_Conditions:
 * Post_Conditions: the players money will be changed in acordance to the num of animals
***/

void Zoo::profit_animals(){
	int tig_p = 0, bea_p = 0, pen_p = 0, inc;
	for(int i = 0; i < num_tiger; i++){
//		money = money + tiger_arr[i].get_pay_off();
//		tig_p = tig_p + tiger_arr[i].get_pay_off();
		money = money + 1000;
		tig_p = tig_p + 1000;
	}
	for(int i = 0; i < num_bear; i++){
		money = money + 250;
		bea_p = bea_p + 250;
	}
	for(int i = 0; i < num_penguine; i++){
//		money = money + penguine_arr[i].get_pay_off();
//		pen_p = pen_p + penguine_arr[i].get_pay_off();
		money = money + 50;
		pen_p = pen_p + 50;
	}
	cout << "Profits per animal:\nTiger: " << tig_p << endl;
	cout << "Bear: " << bea_p << endl;
	cout << "Penguines: " << pen_p << endl;
}

/***
 * Function: feed_animals()
 * Description: this function will do the animal feeding process
 * Parameters: none
 * Pre_Conditions:
 * Post_Conditions: the players money will be changed in acordance to the feed
***/

void Zoo::feed_animals(){
	cout << "\nNumber of tigers: " << num_tiger << endl;
	cout << "Number of Bears: " << num_bear << endl;
	cout << "Number of penguins: " << num_penguine << endl;
	cout << endl;



	int cho1, cho2, cho3, start = 1, cho = 0;
	cho1 = ((tiger_test.get_food_cost(food_price)*(num_tiger)) + (bear_test.get_food_cost(food_price)*(num_bear)) + (penguine_test.get_food_cost(food_price)*(num_penguine))) * 1;
	cho2 = ((tiger_test.get_food_cost(food_price)*(num_tiger)) + (bear_test.get_food_cost(food_price)*(num_bear)) + (penguine_test.get_food_cost(food_price)*(num_penguine))) * 2;
	cho3 = ((tiger_test.get_food_cost(food_price)*(num_tiger)) + (bear_test.get_food_cost(food_price)*(num_bear)) + (penguine_test.get_food_cost(food_price)*(num_penguine))) * 3;
	cout << "What type of feed do you want to use:\n1)Cheap = " << cho1 << "\n2)Normal = " << cho2 << "\n3)Expensive = " << cho3 << "\nCurrent money = " << cur_money() << endl;
	while(start == 1){
		if(money < cho1){
			cout << "Using your remaining cash to pay for food" << endl;
			money = 0;
			food_cho = 1;
			start = 0;
			break;
		}
		cho = get_int();	
		switch(cho){
			case 1:
				if(cur_money() >= cho1){
					sub_money(cho1);
					food_cho = 3;
					start = 0;
				}else{
					cout << "Not enough money" << endl;
				}
				break;
			case 2:
				if(cur_money() >= cho2){
					sub_money(cho2);
					food_cho = 2;
					start = 0;
				}else{
					cout << "Not enough money" << endl;
				}
				break;
			case 3:
				if(cur_money() >= cho3){
					sub_money(cho3);
					food_cho = 1;
					start = 0;
				}else{
					cout << "Not enough money" << endl;
				}
				break;
			default:
				cout << "Invalid choice" << endl;
		}
	}
}

/***
 * Function: rem_tiger_arr
 * Description: this function will remove a specific member of the array
 * Parameters: the spot of the array
 * Pre_Conditions:
 * Post_Conditions:
***/

void Zoo::rem_tiger_arr(int spot){
	Tiger* temp_tiger_arr;
	int loc = spot - 1, temp;
	if((loc <= num_tiger - 1) && (loc >= 0)){
		num_tiger = num_tiger - 1;
		temp_tiger_arr = new Tiger[num_tiger];
		for(int i = 0; i < loc; i++){
			temp_tiger_arr[i] = tiger_arr[i];
		} 
		for(int i = loc + 1; i < num_tiger; i++){
			temp_tiger_arr[i-1] = tiger_arr[i];
		}
		delete [] tiger_arr;
		tiger_arr = new Tiger[num_tiger];
		for(int i = 0; i < num_tiger; i++){
			tiger_arr[i] = temp_tiger_arr[i];
		}
		delete [] temp_tiger_arr;
	}else{
		cout << "Trying to reach an invalid position" << endl;
	}
}

/***
 * Function: add_tiger_agg
 * Description: this function will add an element ot the end of the array
 * Parameters: the tiger being added
 * Pre_Conditions:
 * Post_Conditions:
***/

void Zoo::add_tiger_arr(Tiger new_tiger){
	int temp;
	Tiger* temp_tiger_arr;
	
	num_tiger = num_tiger + 1;
	temp_tiger_arr = new Tiger[num_tiger];
	for(int i = 0; i < num_tiger; i++){
		temp_tiger_arr[i] = tiger_arr[i];
	} 
	delete [] tiger_arr;
	tiger_arr = new Tiger[num_tiger];
	for(int i = 0; i < num_tiger; i++){
		tiger_arr[i] = temp_tiger_arr[i];
	}
	delete [] temp_tiger_arr;
}

//DUPLICATE FUNCTIONS WITH CHANGED TYPES

void Zoo::rem_bear_arr(int spot){
	Bear* temp_bear_arr;
	int loc = spot - 1;
	if((loc <= num_bear - 1) && (loc >= 0)){
		num_bear = num_bear - 1;
		temp_bear_arr = new Bear[num_bear];
		for(int i = 0; i < loc; i++){
			temp_bear_arr[i] = bear_arr[i];
		} 
		for(int i = loc + 1; i < num_bear; i++){
			temp_bear_arr[i-1] = bear_arr[i];
		}
		delete [] bear_arr;
		bear_arr = new Bear[num_bear];
		for(int i = 0; i < num_bear; i++){
			bear_arr[i] = temp_bear_arr[i];
		}
		delete [] temp_bear_arr;
	}else{
		cout << "Trying to reach an invalid position" << endl;
	}
}

void Zoo::add_bear_arr(Bear new_bear){
	Bear* temp_bear_arr;
	num_bear = num_bear + 1;
	temp_bear_arr = new Bear[num_bear];
	for(int i = 0; i < num_bear; i++){
		temp_bear_arr[i] = bear_arr[i];
	} 
	delete [] bear_arr;
	bear_arr = new Bear[num_bear];
	for(int i = 0; i < num_bear; i++){
		bear_arr[i] = temp_bear_arr[i];
	}
	delete [] temp_bear_arr;
}


void Zoo::rem_penguine_arr(int spot){
	Penguine* temp_penguine_arr;
	int loc = spot - 1;
	if((loc <= num_penguine - 1) && (loc >= 0)){
		num_penguine = num_penguine - 1;
		temp_penguine_arr = new Penguine[num_penguine];
		for(int i = 0; i < loc; i++){
			temp_penguine_arr[i] = penguine_arr[i];
		} 
		for(int i = loc + 1; i < num_penguine; i++){
			temp_penguine_arr[i-1] = penguine_arr[i];
		}
		delete [] penguine_arr;
		penguine_arr = new Penguine[num_penguine];
		for(int i = 0; i < num_penguine; i++){
			penguine_arr[i] = temp_penguine_arr[i];
		}
		delete [] temp_penguine_arr;
	}else{
		cout << "Trying to reach an invalid position" << endl;
	}
}

void Zoo::add_penguine_arr(Penguine new_penguine){
	Penguine* temp_penguine_arr;
	num_penguine = num_penguine + 1;
	temp_penguine_arr = new Penguine[num_penguine];
	for(int i = 0; i < num_penguine; i++){
		temp_penguine_arr[i] = penguine_arr[i];
	} 
	delete [] penguine_arr;
	penguine_arr = new Penguine[num_penguine];
	for(int i = 0; i < num_penguine; i++){
		penguine_arr[i] = temp_penguine_arr[i];
	}
	delete [] temp_penguine_arr;
}
