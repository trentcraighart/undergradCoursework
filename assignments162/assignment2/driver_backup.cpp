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

	deck bj_deck;
	player* all_players;
	srand(time(NULL));

	dealer bj_dealer;
	player newplayer(0, 0);
	cout << "How many players: ";
	int cat;
	cin >> cat;
	all_players = new player[cat];
		
	for(int i=0; i<cat; i++){
		all_players[i] = player(i, 10);
	}
		
		
	int game_run = 1;
	while(game_run == 1){
		for(int i=0; i<cat; i++){
			all_players[i].reset_tot();
		}	
		bj_dealer.reset();
		for(int i=0; i<cat; i++){
			cout << "MAKING BET FOR PLAYER: " << i << endl;
			all_players[i].make_bet(i);
		}
		bj_deck.pop_cards();
		bj_dealer.get_first(bj_deck);

		
		for(int i=0; i<cat; i++){
			cout << "Player " << i << " drew:" << endl;
			all_players[i].get_start_hand(bj_deck);		
		}
		for(int i=0; i<cat; i++){
			int hit = 1;
			while(hit == 1 && all_players[i].return_tot() < 21){
				cout << "Player " << i <<"s current hand total: ";
				all_players[i].display_tot();
				cout << "\n\nDo you want to hit?: (y) = yes" << endl;
				string cho = "n";
				cin >> cho;
				if(cho != "y"){
					hit = 0;
				}else{
					all_players[i].get_card(bj_deck);
				}
			}
		}
		bj_dealer.play(bj_deck);
		
		for(int i=0; i<cat; i++){
			if(all_players[i].return_tot() == 21){
				cout << "Player: "<< i << " hit 21!" << endl;
				all_players[i].big_win();	
			}else if((all_players[i].return_tot() > bj_dealer.return_tot() && all_players[i].return_tot() < 21) || (all_players[i].return_tot() < 21 && bj_dealer.return_tot() > 21)){
				cout << "Player: "<< i << " won!" << endl;
				all_players[i].win();
			}else if(all_players[i].return_tot() < bj_dealer.return_tot() || all_players[i].return_tot() > 21){
				cout << "Player: "<< i << " lost!" << endl;
				all_players[i].lose();
			}else{
				cout << "Player: "<< i << " tied!" << endl;
			}
		}
		
		cout << "Current Scores: \n\n";
		for(int i=0; i<cat; i++){
			cout << "\nPlayer " << i << "'s total: ";
			all_players[i].out_tot();
		}

		string value;
		cout << "\nDo You want to continue: (y) or (n)" << endl;
		cin  >> value;
		if(value != "y"){
			game_run = 0;
		}
	}
	return 0;
}

