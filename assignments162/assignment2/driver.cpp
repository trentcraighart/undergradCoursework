/****************
 *Program: blackjack.exe
 *Author: Trent Vasquez
 *Date: 04/20/2016
 *Description: Plays blackjack
****************/


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "deck.h"
#include "card.h"
#include "player.h"
#include "dealer.h"
#include "game.h"

using namespace std;

int main(){
	srand(time(NULL));

	cout << "How many players: ";
	int cat;
	cin >> cat;
	
	game bj_game(cat);
	bj_game.run_game(cat);
		
	
	return 0;
}

