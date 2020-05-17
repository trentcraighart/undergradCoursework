#include "eve_pit.h"

void Eve_Pit::set_event(){
	set_message("You feel a breeze");
	set_status(1);
}

void Eve_Pit::exe_event(Player* cur){
	cout << "There is a pit in the room" << endl;
	int act = (*cur).action();
	if(act == 0){
		cout << "You fall into the pit and die!" << endl;
		(*cur).set_coord();
		(*cur).die();
	}else{
		(*cur).miss_arrow();
		cout << "Your you here your arrow hit the bottem of a chasm" << endl;
	}
}
