#ifndef animal_h
#define animal_h

#include <cstdlib>

class Animal{
	protected:
	int age, num_baby, price, food_mult, pay_off;

	public:
	Animal();
	int get_pay_off();
	int get_food_cost(int);
	int get_age();
	void age_up();
};

#endif


