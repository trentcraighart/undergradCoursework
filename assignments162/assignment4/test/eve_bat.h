#ifndef eve_bat_h
#define eve_bat_h

#include <iostream>
#include <cstdlib>
#include <string>
#include "event.h"

using namespace std;

class Eve_Bat: public Event{
	private:

	public:
	void set_event();
	void exe_event(Player*);
};

#endif
