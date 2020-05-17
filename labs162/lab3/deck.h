#include "./card.h"
#include <string>
class deck{
	private:
		struct card cards[52];
		int num_cards;

	public:

	void pop_cards(string suit, int card_num);
	void shuffle();
	void draw_card();
};
