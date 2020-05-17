#ifndef eve_gold_h
#define eve_gold_h

#include <iostream>
#include <cstdlib>
#include <string>
#include "event.h"

using namespace std;

class Eve_Gold: public Event{
	private:

	public:
	void set_event();
	void exe_event(Player*);
};

#endif
