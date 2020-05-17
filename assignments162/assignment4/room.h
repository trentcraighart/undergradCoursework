#ifndef room_h
#define room_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include "event.h"

using namespace std;

class Room{
	private:
	int num_events;
	vector<Event *> events;
	public:
	Room();
	void add_event(Event*);
	void remove_event();
	void inc_num();
	void dec_num();
	void output_top_room();
	int is_empty();
	int out_num_events();
	int get_top_status();
	int get_top_event();
	void run_event(Player*);
	void near();
	~Room();
};

#endif
