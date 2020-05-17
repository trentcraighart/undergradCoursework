#ifndef player_h
#define player_h

#include "card.h"
#include "deck.h"
#include <iostream>

class player{
//	public:
	private:
	card cur_car;
	int cur_bet;
	int cur_hand_val;
	int bust;
	int bj;
	int player_number;
	int tot_money;

	public:

	player();
	player(int player_num, int total);

	
	void reset_tot();
	int return_tot();
	void display_tot();
	void get_card(deck&);
	int test_for_int();
	void get_start_hand(deck&);
	void make_bet(int&);
	void win();
	void big_win();
	void lose();
	void out_tot();
};

#endif
