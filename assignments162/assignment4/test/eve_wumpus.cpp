#include "eve_wumpus.h"

void Eve_Wumpus::set_event(){
	set_message("You smell a foul oder");
	set_status(2);
}

void Eve_Wumpus::exe_event(Player* cur){
	cout << "You see the Wumpus" << endl;
	int act = (*cur).action();
	if(act == 0 && is_dead() == 0){
		cout << "You are devoured by the Wumpus" << endl;
		(*cur).set_coord();
		(*cur).die();
	}
	if(act == 0 && is_dead() == 1){
		cout << "You pass by its corpse" << endl;
		(*cur).set_coord();
	}
	if(act == 1 && is_dead() == 1){
		(*cur).miss_arrow();
		cout << "You shoot the wumpus courpse" << endl;
	}
	if(act == 1 && is_dead() == 0){
		(*cur).miss_arrow();
		cout << "You shoot an arrow at the Wumpus" << endl;
		int hit = rand() % 4;
		if(hit == 3){
			cout << "You missed the wumpus" << endl;
			(*cur).missed_wumpus();
		}else{
			cout << "You killed the wumpus with your arrow" << endl;
			(*cur).killed_wumpus();
			died();
		}
	}
}

