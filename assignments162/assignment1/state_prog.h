#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

//Prototypes
int test_command(int, char*[], int*, char**);
int test_for_int();
struct state * create_states(int, char**);
void delete_memory(struct state *, int);
void function_menu(struct state *, int, char**);
void large_state(struct state *, int);
void state_by_name(struct state *, int);
void largest_county(struct state *, int);
void counties_above(struct state *, int);
void average_house(struct state *, int);

struct county{
	string county;
	string *city;
	int cities;
	int population;
	int avg_income;
	int avg_house;
};

struct state{
	string name;
	struct county *c;
	int counties;
	int population;
};

