#ifndef game_h
#define game_h


#include "card.h"
#include "deck.h"
#include "player.h"
#include "dealer.h"

using namespace std;

class game{
	private:
	int cat;
	player* all_players;	
//	deck bj_deck;
//	dealer bj_dealer;

	public:
	game(int);
	void run_game(int);
	~game();
};

#endif
