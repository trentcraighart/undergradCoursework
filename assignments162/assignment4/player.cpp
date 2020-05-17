#include "player.h"

Player::Player(){
	num_arrows = 3;
	has_found_gold = 0;
	has_killed_wumpus = 0;
	has_die = 0;
	miss = 0;
}

void Player::set_start(Map cur_map){
	x_map = cur_map.out_width();
	y_map = cur_map.out_length();
	int loc = 1;
	while(loc != 0){
		x_start = rand() % cur_map.out_width();
		y_start = rand() % cur_map.out_length();
		loc = cur_map.return_status(x_start, y_start);
	}
	x_coord = x_start;
	y_coord = y_start;
}

int Player::home(){
	if(x_coord == x_start && y_coord == y_start){
		return 1;
	}else{
		return 0;
	}
}

void Player::random_move(){
	x_coord = rand() % x_map;
	y_coord = rand() % y_map;
}

void Player::get_action(Map cur_map){
	miss = 0;
	#ifdef DEBUG
	cout << "Current x_coord is " << x_coord + 1 << endl;
	cout << "Current y_coord is " << y_coord + 1 << endl;
	#endif
	int choice;
	cout << "What action do you want to preform, (0) move (1) shoot" << endl;
	choice = get_int();
	switch(choice){
		case 0:
			cout << "Move" << endl;
			acti = 0;
			preform_action(cur_map);
			break;
		case 1:
			if(num_arrows == 0){
				cout << "You're our of arrows" << endl;
				break;
			}
			cout << "Shoot" << endl;
			acti = 1;
			preform_action(cur_map);
			break;
		default:
			cout << "Not a valid option" << endl;
	}
}

void Player::output_near(Map cur_map){	
		cur_map.output_near(x_coord, y_coord);
/*		int cur_x = cur_map.out_width();
		int cur_y = cur_map.out_length();
		if(x_coord > 0){
			cur_map.check_event(temp_x - 1, temp_y);
		}
		if(x_coord < cur_x - 2){
			cur_map.check_event(temp_x + 1, temp_y);
		}
		if(y_coord > 0){
			cur_map.check_event(temp_x, temp_y - 1);
		}
		if(y_coord < cur_y - 2){
			cur_map.check_event(temp_x, temp_y + 1);
*/	
}

void Player::preform_action(Map cur_map){
	int choice;
	temp_x = x_coord;
	temp_y = y_coord;
	cout << "(1) Up, (2) Right, (3) Down, (4) Left: ";
	choice = get_int();
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	switch(choice){
		case 3:
			temp_y = temp_y + 1;
			break;
		case 2:
			temp_x = temp_x + 1;
			break;
		case 1:
			temp_y = temp_y - 1;
			break;
		case 4:
			temp_x = temp_x - 1;
			break;
		default:
			cout << "Invalid direction" << endl;
			choice = 0;
	}
	if(choice != 0){
		int cur_x = cur_map.out_width();
		int cur_y = cur_map.out_length();
		if(temp_x >= 0 && temp_y >= 0 && temp_x < cur_x && temp_y < cur_y){
			cur_map.run_event(temp_x, temp_y, &*this);
		}else{
			cout << "There seams to be a wall in that direction\n" << endl;
		}
	}
}

void Player::print_prog(){
	cout << "Killed wumpus = " << has_killed_wumpus << endl;
	cout << "Found gold = " << has_found_gold << endl;
	#ifdef DEBUG
	cout << "Home coordinate: ";
	cout << "(" << x_start+1 << "," << y_start+1 << ")" << endl;
	#endif
	cout << "\n\n" << endl;
}

void Player::missed_wumpus(){
	cout << "The wumpus gets up" << endl;
	cout << "The wumpus doesn't move" << endl;
}

int Player::out_gold(){
	return has_found_gold;	
}


int Player::out_wumpus(){
	return has_killed_wumpus;	
}


int Player::out_die(){
	return has_die;	
}

void Player::set_coord(){
	x_coord = temp_x;
	y_coord = temp_y; 
}

void Player::miss_arrow(){
	num_arrows = num_arrows - 1;
}

void Player::test_function(){
	cout << "Test function" << endl;
}

int Player::action(){
	return acti;
}

void Player::die(){
	has_die = 1;
}
void Player::killed_wumpus(){
	has_killed_wumpus = 1;	
}
	
void Player::found_gold(){
	has_found_gold = 1;
}
