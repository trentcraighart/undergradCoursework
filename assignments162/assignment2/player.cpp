#include "player.h"
#include <cstdlib>

using namespace std;


player::player(){
	player_number = -1;
	tot_money = 10;
	card cur_card;
	cur_card.value = 0;
	cur_bet = 0;
	cur_hand_val = 0;
	bust = 0;
	bj = 0;
}
player::player(int player_num, int total){
	player_number = player_num;
	tot_money = total;
	card cur_card;
	cur_card.value = 0;
	cur_bet = 0;
	cur_hand_val = 0;
	bust = 0;
	bj = 0;
}


void player::display_tot(){
	cout << cur_hand_val;
}

int player::return_tot(){
	return cur_hand_val;
}

void player::get_start_hand(deck& gdeck){
	get_card(gdeck);
	get_card(gdeck);
}

void player::get_card(deck& gdeck){
	int opt = 0, cho = 0;
	cur_car = gdeck.draw_card();
	if(cur_car.value == 1){
		opt = 1;
		while(opt == 1){
			cout << "You drew an ACE, would you want a 1 or 11? (1)-1 (2)-11 ";
			cho = test_for_int();
			if(cho == 1){
				cur_hand_val = cur_hand_val + 1;
				opt = 0;	
			}
			if(cho == 2){
				cur_hand_val = cur_hand_val +11;
				opt = 0;
			}
		}
	}else{
		cur_hand_val = cur_hand_val + cur_car.value;
	}
}

void player::make_bet(int& p_num){
	int player_num = p_num;
	cout << "\nPlayer " << p_num << "'s turn!" << endl;
	int pro = 0, val;
	if(tot_money < 1){
		cout << "The bank is giving you 1$ " << endl;
		tot_money = 1;
	}
	cout << "Current Money: " << tot_money << endl;
	cout << "Make your bet (as an int): ";
	while(pro==0){
		val = test_for_int();
		if(val <= tot_money){
			cur_bet = val;
			pro = 1;
		}else{
			cout << "invalid, new bet: ";
		}
	}
}

int player::test_for_int(){
	int i, test, valuef;
	bool start = true;
	test = 0;
	string value;
	while(start==true){
		test = 0;
		cin >> value;
		for(int i = 0; i < value.size(); i++){
			if(value[i]<=57 && value [i]>=48){
				test += 1;
			}else{
				cout << "Invalid input\nNew input: ";
			}
			if(test==value.size()){
				start = false;
			}
		}
	}
	valuef = atoi(value.c_str());
	return valuef;
}

void player::reset_tot(){
	cur_hand_val = 0;
}

void player::win(){
	tot_money = tot_money + cur_bet;
}

void player::big_win(){
	tot_money = tot_money + (cur_bet * 1.5);
}

void player::lose(){
	tot_money = tot_money - cur_bet;
}

void player::out_tot(){
	cout << tot_money;
}
