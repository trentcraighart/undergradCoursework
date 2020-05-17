#ifndef map_h
#define map_h

#include <iostream>
#include "room.h"

using namespace std;

class Map{
	private:
	struct Room** game_map;
	int width;
	int length;

	public:
	Map();
	Map(int, int);
	void make_map();
	void set_events();
	void print_map();
	int out_width();
	int out_length();
	void output_near(int, int);
	int return_status(int, int);
	void run_event(int, int, struct Player*);
	void check_event(int, int);	
	//~Map();

};

#endif
