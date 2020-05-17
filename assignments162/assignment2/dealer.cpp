#include "dealer.h"

using namespace std;

dealer::dealer(){
	card cur_card;
	cur_card.value = 0;
	cur_hand_tot = 0;
	bust = 0;
	bj = 0;

	cur_card.suit = ' ';
	cur_card.value = 0;
	cur_card.dealt = 0;
	cur_card.flipped = 0;
	cur_card.name = ' ';
	cur_card.is_named = 0;
}

void dealer::get_first(deck& gdeck){
	cur_hand_tot = get_card(gdeck);
}

void dealer::add_card(deck& gdeck){
	cur_hand_tot = cur_hand_tot + get_card(gdeck);
}

void dealer::play(deck& gdeck){
	int opt = 1;
	do{
		if(cur_hand_tot < 16){
			cout << "Dealer Hit" << endl;
			get_card(gdeck);
		}else{
			cout << "Dealer Stays at: " << cur_hand_tot <<  endl;
			opt = 0;
		}
	}while(opt == 1);
}

int dealer::get_card(deck& gdeck){
	cout << "The dealer drew" << endl;
	cur_card = gdeck.draw_card();
	cout << "Suit " << cur_card.suit << " Value " << cur_card.value << cur_card.name << "\n" << endl;
	if(cur_card.value == 1){
		if(cur_hand_tot <= 10){
			cur_hand_tot = cur_hand_tot + 11;
		}else{
			cur_hand_tot = cur_hand_tot +1;
		}
	}else{
		cur_hand_tot = cur_hand_tot + cur_card.value;
	}
	
	cout << "Dealer's Current Hand Value: " << cur_hand_tot << endl;
	return cur_hand_tot;
}

void dealer::reset(){
	cur_hand_tot = 0;
}

int dealer::return_tot(){
	return cur_hand_tot;
}
