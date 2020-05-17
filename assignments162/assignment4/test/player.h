#ifndef player_h
#define player_h

#include <iostream>
#include <cstdlib>
#include "functions.h"
#include "map.h"

using namespace std;

class Player{
	private:
	int num_arrows;
	int has_found_gold;
	int x_coord;
	int y_coord;
	int x_start;
	int y_start;
	int acti;
	int temp_x;
	int temp_y;
	int has_die;
	int has_killed_wumpus;
	int x_map;
	int y_map;
	int miss;

	public:
	Player();
	void print_prog();
	int home();
	void random_move();
	void set_start(Map);
	void get_action(Map);
	void preform_action(Map);
	void set_coord();
	void miss_arrow();
	void test_function();
	int action();
	void killed_wumpus();
	void found_gold();
	void missed_wumpus();
	int out_gold();
	int out_wumpus();
	int out_die();
	void output_near(Map);
	void die();
};

#endif
