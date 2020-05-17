#ifndef eve_nothing_h
#define eve_nothing_h

#include <iostream>
#include <cstdlib>
#include <string>
#include "event.h"

using namespace std;

class Eve_Nothing: public Event{
	private:

	public:
	void set_event();
	void exe_event(Player*);
};

#endif
