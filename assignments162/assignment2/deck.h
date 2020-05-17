#ifndef deck_h
#define deck_h

#include "card.h"

class deck{
	private:

	card* gdeck;
	int cards_left;


	public:
	deck();
	void pop_cards();
	void shuffle();
	card draw_card();
	~deck();
	
};

#endif
