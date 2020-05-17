#include "game.h"
#include <cstring>
using namespace std;


game::game(int dog){
	int cat = dog;
	player* all_players;
	all_players = new player[cat];
}

void game::run_game(int cat){

	player* all_players;
	all_players = new player[cat];

	deck bj_deck;
	dealer bj_dealer;

	for(int i=0; i<cat; i++){
		all_players[i] = player(i, 10);
	}
		
	string game_run = "y";
	while(game_run == "y"){
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
				cout << "Player: " << i << " won!" << endl;
				all_players[i].win();
			}
		}
	cout << "Do you still want to play, (y) for yes: ";
	cin >> game_run;
	}
}

game::~game(){
	delete all_players;
}
