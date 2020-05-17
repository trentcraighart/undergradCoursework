#ifndef hand_h
#define hand_h
#include "deck.h"


class hand{
	public:
	hand();
	void set_card(deck);
	void hit(deck);
	card * get_cards() const;
	void create_cards(const int);
	int get_num_cards() const;

	private:
	card gcard[7];

		
};
#endif
