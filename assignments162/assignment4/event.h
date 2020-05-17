#ifndef event_h
#define event_h

#include <iostream>
#include <cstdlib>
#include <string>
#include "player.h"

using namespace std;

class Event{
	private:
	string message;
	int status;
	int has_died;

	public:
	Event();
	void output_message();
	int return_status();
	void output_status();
	void set_message(string);
	void set_status(int);
	void died();
	int is_dead();
	virtual void set_event() = 0;
	virtual void exe_event(Player*) = 0;
};

#endif
