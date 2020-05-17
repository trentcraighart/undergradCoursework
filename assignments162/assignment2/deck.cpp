#include "deck.h"
#include <cstdlib>
#include <time.h>

using namespace std;

deck::deck(){
	cout << "New Deck" << endl;
	card *gcard;
	gdeck = new card[52];
	int cards_left = 52;
	for(int b=0; b<52; b++){
		gdeck[b].suit = ' ';
		gdeck[b].value = 0;
		gdeck[b].dealt = 0;
		gdeck[b].flipped = 0;
		gdeck[b].name = ' ';
		gdeck[b].is_named = 0;
	}
}

card deck::draw_card(){
	if(cards_left==1){
		shuffle();
		cout << "New Deck" << endl;
	}
	int valid_card = 0;
	int num;
	num = rand() % 52;
	do{
		if(gdeck[num].dealt == 0){
			if(num == 1){
				gdeck[num].value = 1;
			}
			cards_left = cards_left-1;
			gdeck[num].dealt = 1;
			valid_card = 1;
		}else{
			if(num == 51){
				num = 0;
			}else{
				num++;
			}
		}
	}while(valid_card == 0);
	cout << "Suit " << gdeck[num].suit << " Value " << gdeck[num].value << gdeck[num].name << "\n" << endl;
	
	return gdeck[num];
}

void deck::shuffle(){
	cout << "Shuffle" << endl;
	cards_left = 52;
	for(int i=0; i<52; i++){
		gdeck[i].dealt = 0;
	}
}

void deck::pop_cards(){
	shuffle();
	for(int i=0; i<52; i++){
		gdeck[i].name = ' ';
	}
	for(int i=0; i<52; i = i+4){
		gdeck[i].suit = 'c';
		gdeck[i+1].suit = 's';
		gdeck[i+2].suit = 'd';
		gdeck[i+3].suit = 'h';
	}
	for(int i=1; i<14; i++){
		int k = ((i-1)*4);
		if(i==1){
			for(int j=0; j<4; j++){
				gdeck[j+k].value = 1;
				gdeck[j+k].is_named = 1;
				gdeck[j+k].name = 'A';
			}
		}
		if(1<i && i<11){
			for(int j=0; j<4; j++){
				gdeck[j+k].value = i;
				gdeck[j+k].is_named = 0;
			}
		}
		if(i==11){
			for(int j=0; j<4; j++){
				gdeck[j+k].value = 10;
				gdeck[j+k].is_named = 1;
				gdeck[j+k].name = 'J';
			}
		}
		if(i==12){
			for(int j=0; j<4; j++){
				gdeck[j+k].value = 10;
				gdeck[j+k].is_named = 1;
				gdeck[j+k].name = 'Q';
			}
		}
		if(i==13){
			for(int j=0; j<4; j++){
				gdeck[j+k].value = 10;
				gdeck[j+k].is_named = 1;
				gdeck[j+k].name = 'K';
			}
		}
	}
	cards_left = 52;
}

deck::~deck(){
	delete [] gdeck;
}
