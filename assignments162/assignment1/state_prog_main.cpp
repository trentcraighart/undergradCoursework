#include "state_prog.h"
/***
 *Program Filename:state_prog.exe
 *Author: Trent Vasquez
 *Date: 04/10/2016
 *Description: This program can read into a file and help interpret state information
 **/

int main(int argc, char *argv[]){
	int valid = 1, state, temp;
	char *file_name;
	struct state * list;
	valid = test_command(argc, argv, &state, &file_name);
	temp = atoi(argv[2]);
	list = create_states(state, &file_name);
	function_menu(list, temp, &file_name);
	return 0;
}
