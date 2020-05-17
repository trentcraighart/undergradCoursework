#include "./deck.h"


using namespace std;

void deck::shuffle(){
	for(int i=0; i<52; i++){
		cards[i].dealt = false;
	}
}

void deck::pop_cards(string suit, int card_num){
	for(int i=card_num; i<card_num+13; i++){
		cards[i].value = i-card_num;
		cards[i].suit = suit;
	}
}


