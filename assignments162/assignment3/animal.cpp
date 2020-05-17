#include "animal.h"

Animal::Animal(){
	age = 3;
	num_baby = 1;
	price = 1000;
	food_mult = 1;
	pay_off = 100;
}

int Animal::get_pay_off(){
	return pay_off;
}

int Animal::get_food_cost(int base_food){
	return (food_mult)*(base_food);
}

int Animal::get_age(){
	if(age>10){
		return 3;
	}else{
		return age;
	}
}

void Animal::age_up(){
	age = age+1;
}
