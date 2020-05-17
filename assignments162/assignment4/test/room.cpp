#include "room.h"


Room::Room(){
	int num_events = 0;
}

void Room::inc_num(){
	num_events++;
}

void Room::dec_num(){
	num_events = num_events - 1;
}

/***
 * add_event will take an event as the parameter then it will add it to the end of the vector
***/

void Room::add_event(Event *new_event){
	events.push_back(new_event);
	inc_num();
}

/***
 * remove_event will remove the top event in the array of events
 * Note: The idea is that the only way two events will stack is if the wumpus is in the room, thus the other event doesn't matter
***/

void Room::remove_event(){
	events.pop_back();
	dec_num();
}

/***
 * get_top_event will acces the top event in the array of events
 * Note: The idea is that the only way two events will stack is if the wumpus is in the room, thus the other event doesn't matter
***/

int Room::get_top_event(){
	return events.at(num_events - 1)->return_status();
}

int Room::is_empty(){
	if(num_events == 0){
		return 1;
	}else{
		return 0;
	}
}

int Room::out_num_events(){
	return num_events;
}

void Room::near(){
	events.at(num_events - 1)->output_message();
}

void Room::output_top_room(){
	events.at(num_events - 1)->output_status();
}

void Room::run_event(Player* cur_player){                 //Events is a vector of events (polymorphic)
//	(*cur_player).test_function();                    //This Function works
	events.at(num_events - 1)->exe_event(cur_player); //This Function seg faults
//	events[num_events - 1]->exe_event(cur_player);    //This Function seg faults
}

Room::~Room(){
	cout << "Room Deleted" << endl;
}
