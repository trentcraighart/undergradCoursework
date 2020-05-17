#include <iostream>
#include <cstdlib>
#include <vector>
#include "room.cpp"
#include "functions.cpp"
#include "event.cpp"
#include "eve_bat.cpp"
#include "eve_gold.cpp"
#include "player.cpp"
#include "eve_wumpus.cpp"
#include "eve_pit.cpp"
#include "eve_nothing.cpp"
#include "map.cpp"

using namespace std;

int main(int argc, char *argv[]){
	srand(time(NULL));
	cout << "Begining of program\n\n\n\n\n\n\n\n\n\n" << endl;
	
	cout << "In the game HUNT THE WUMPUS, you have three goals:\n(1)Steal the gold" << endl;
	cout << "(2)Kill the wumpus\n(3)Make it back to your starting tile\n\nGOOD LUCK!" << endl;
	
	int run = 1;
	while(run == 1){
		int x = 6, y = 6;
		if(argc == 3){	
			x = atoi(argv[1]);
			y = atoi(argv[2]);
		}
		Map game_map(x, y);

		game_map.make_map();
		game_map.set_events();		
		
		Player game_player;
		game_player.set_start(game_map);
			
		int die = 0, gold = 0, wumpus = 0, home=0;
		while(die == 0 && (wumpus == 0 || gold == 0 || home == 0)){
			#ifdef DEBUG
			game_map.print_map();
			#endif
			game_player.output_near(game_map);
			game_player.get_action(game_map);
			game_player.print_prog();
			gold = game_player.out_gold();
			wumpus = game_player.out_wumpus();
			die = game_player.out_die();
			home = game_player.home();
		}
	if(die == 1){
		cout << "Game over, you died!" << endl;
	}else{
		cout << "You've defeated the Wumpus!\n\nCONGRATULATIONS\n\n" << endl;
	}
	cout << "If you want to play again, enter the number 1" << endl;
	run = get_int();	
	}

	cout << "End of program" << endl;

	return 0;

}
