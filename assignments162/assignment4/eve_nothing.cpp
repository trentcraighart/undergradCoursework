#include "eve_nothing.h"

void Eve_Nothing::set_event(){
	set_message("No Event Here");
	set_status(0);
}

void Eve_Nothing::exe_event(Player* cur){
	cout << "The room is empty" << endl;
	int act = cur->action();
	if(act == 0){
		cur->set_coord();
	}else{
		cur->miss_arrow();
	}
}
