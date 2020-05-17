#ifndef eve_pit_h
#define eve_pit_h

#include <iostream>
#include <cstdlib>
#include <string>
#include "event.h"

using namespace std;

class Eve_Pit: public Event{
	private:

	public:
	void set_event();
	void exe_event(Player*);

};

#endif
