#include "bear.h"

Bear::Bear(){
	age = 3;
	num_baby = 2;
	price = 5000;
	food_mult = 3;
	pay_off = 250;	
}

Bear::Bear(int age){
	this->age = age;
	num_baby = 2;
	price = 5000;
	food_mult = 3;
	pay_off = 250;
}
