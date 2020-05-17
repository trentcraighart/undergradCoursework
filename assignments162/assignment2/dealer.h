#ifndef dealer_h
#define dealer_h

#include "card.h"
#include "deck.h"

class dealer{
	private:
	card cur_card;
	int cur_hand_tot;
	int bust;
	int bj;

	public:

	dealer();
	void reset();	
	void play(deck&);
	void get_first(deck&);
	int get_card(deck&);
	int return_tot();
	void add_card(deck&);
};

#endif
