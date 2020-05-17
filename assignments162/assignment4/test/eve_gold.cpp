#include "eve_gold.h"

void Eve_Gold::set_event(){
	set_message("You see a glimer out of the corner of your eye");
	set_status(3);
}

void Eve_Gold::exe_event(Player* cur){
	cout << "You've found the Wumpus treasure" << endl;
	int act = (*cur).action();
	if(act == 0){
		cout << "You've collected the treasure" << endl;
		(*cur).found_gold();
		(*cur).set_coord();
	}
	if(act == 1){
		cout << "Your arrow hits gold" << endl;
		(*cur).miss_arrow();
	}
}
