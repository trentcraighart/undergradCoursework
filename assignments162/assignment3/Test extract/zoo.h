#ifndef zoo_h
#define zoo_h

//#include "bear.h"
//#include "tiger.h"
//#include "penguine.h"

class Zoo{
	protected:
	int food_price, day, money, num_tiger, num_bear, num_penguine, num_animals, food_cho;
	Tiger* tiger_arr;
	Bear* bear_arr;
	Penguine* penguine_arr;
	Bear bear_test;
	Tiger tiger_test;
	Penguine penguine_test;

	public:
	Zoo();
	~Zoo();
	void rem_tiger_arr(int);
	void add_tiger_arr(Tiger);
	void rem_bear_arr(int);
	void add_bear_arr(Bear);
	void rem_penguine_arr(int);
	void add_penguine_arr(Penguine);
	int cur_money();
	void sub_money(int);
	void inc_day();
	int out_day();
	void feed_animals();
	void profit_animals();
	void random_event();
	void animal_death();
	void boom();
	void birth();
	void inc_age();
};

#endif


