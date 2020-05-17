#include "event.h"

Event::Event(){
	message = "";
	status = 0;
	has_died = 0;
}

void Event::output_message(){
	cout << message << endl;;
}

void Event::output_status(){
	cout << status;
}

int Event::return_status(){
	return status;
}

void Event::set_message(string mess){
	message = mess;
}

void Event::set_status(int stat){
	status = stat;
}

void Event::died(){
	has_died = 1;
}

int Event::is_dead(){
	return has_died;
}

