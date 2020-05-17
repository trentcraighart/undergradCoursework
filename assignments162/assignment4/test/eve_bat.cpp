#include "eve_bat.h"

void Eve_Bat::set_event(){
	set_message("You hear wings flapping");
	set_status(4);
}

void Eve_Bat::exe_event(Player* cur){
	cout << "You hear the chatter of bats" << endl;
	int act = (*cur).action();
	if(act == 0){
		cout << "You get grabed by some bats and taken somewhere else" << endl;
		(*cur).random_move();
	}else{
		(*cur).miss_arrow();
		cout << "Your arrow strikes a bat, but you realize there are many more" << endl;
	}
}
