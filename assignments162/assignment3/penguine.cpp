#include "penguine.h"

Penguine::Penguine(){
	age = 3;
	num_baby = 3;
	price = 1000;
	food_mult = 1;
	pay_off = 50;	
}

Penguine::Penguine(int age){
	this->age = age;
	num_baby = 3;
	price = 1000;
	food_mult = 1;
	pay_off = 50;
}
