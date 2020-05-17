#include "deck.h"
#include <cstdlib>
#include <time.h>


hand::hand(){
	int total = 0;
	int found_cards = 0;


}

void hand::set_cards(deck bj){
	bool valid_card = false;
	srand(time(NULL));
	while(found_cards < 2){
		while(valid_card == false){
			int num = rand() % 51;
			if(bj.cards[num].dealt == false){
				gcard[found_cards] = bj.cards[num];
				valid_card = true;
			}
		}
		found_cards++;
		valid_card = false;
	}
}

void hit(deck bj){












}


