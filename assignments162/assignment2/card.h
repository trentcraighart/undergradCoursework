#ifndef card_h
#define card_h

#include <iostream>

using namespace std;

struct card{
	char suit;
	int value;
	int dealt;
	int flipped;
	char name;
	int is_named;
};

#endif
