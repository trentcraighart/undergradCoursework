#ifndef eve_wumpus_h
#define eve_wumpus_h

#include <iostream>
#include <cstdlib>
#include <string>
#include "event.h"

using namespace std;

class Eve_Wumpus: public Event{
	private:

	public:
	void set_event();
	void exe_event(Player*);
};

#endif
