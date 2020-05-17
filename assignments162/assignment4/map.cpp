#include "map.h"
#include "room.h"
#include "event.h"
#include "eve_bat.h"
#include "eve_pit.h"
#include "eve_gold.h"
#include "eve_wumpus.h"
#include "eve_nothing.h"

Map::Map(){
	width = 6;
	length = 5;
	Eve_Nothing* test_nothing;
	Eve_Pit* test_pit;
	Eve_Bat* test_bat;
	Eve_Gold* test_gold;
	Eve_Wumpus* test_wumpus;
}
Map::Map(int x, int y){
	width = x;
	length = y;
	Eve_Nothing* test_nothing;
	Eve_Pit* test_pit;
	Eve_Bat* test_bat;
	Eve_Gold* test_gold;
	Eve_Wumpus* test_wumpus;
}


void Map::make_map(){
	if(length < 4){
		length = 4;
	}
	if(width < 4){
		width = 4;
	}
	if(width * length < 10 && width != 0 && length != 0){
		width = 3;
		length = 3;
	}
	game_map = new Room *[width];
	for(int i = 0; i < width; i++){
		game_map[i] = new Room[length];
	}
}

void Map::set_events(){
	cout << "\n\n\n\n\n" << endl;
	Eve_Bat* test_bat = new Eve_Bat;
	Eve_Pit* test_pit = new Eve_Pit;
	Eve_Nothing* test_nothing = new Eve_Nothing;
	Eve_Gold* test_gold = new Eve_Gold;
	Eve_Wumpus* test_wumpus = new Eve_Wumpus;

/*
	Eve_Bat* adr_bat;
	adr_bat = &test_bat;

	Eve_Pit* adr_pit;
	adr_pit = &test_pit;

	Eve_Nothing* adr_nothing;
	adr_nothing = &test_nothing;
*/
	test_bat->set_event();
	test_pit->set_event();
	test_nothing->set_event();
	test_gold->set_event();
	test_wumpus->set_event();

	int bat = 2, pit = 2, gold = 1, wumpus = 1, total = 6, x, y, empty;
	while(bat > 0){
		x = rand() % width;
		y = rand() % length;
		empty = game_map[x][y].is_empty();
		if(empty == 1){
			game_map[x][y].add_event(test_bat);
			bat = bat - 1;
		}
	}
	cout << "Bats have finished nesting" << endl;
	while(pit > 0){
		x = rand() % width;
		y = rand() % length;
		empty = game_map[x][y].is_empty();
		if(empty == 1){
			game_map[x][y].add_event(test_pit);
			pit = pit - 1;
		}
	}
	cout << "The pits have been dug" << endl;
	while(gold > 0){
		x = rand() % width;
		y = rand() % length;
		empty = game_map[x][y].is_empty();
		if(empty == 1){
			game_map[x][y].add_event(test_gold);
			gold = gold - 1;
		}
	}
	cout << "The gold has been hidden" << endl;
	while(wumpus > 0){
		x = rand() % width;
		y = rand() % length;
		empty = game_map[x][y].is_empty();
		if(empty == 1){
			game_map[x][y].add_event(test_wumpus);
			wumpus = wumpus - 1;
		}
	}
	cout << "The wumpus is taking a nap" << endl;
	for(int i = 0; i < width; i++){
		for(int j = 0; j < length; j++){
			empty = game_map[i][j].is_empty();
			if(empty == 1){
				game_map[i][j].add_event(test_nothing);
			}
		}
	}
	cout << "Finished constructing the Wumpus lair \n\n" << endl;
	#ifdef DEBUG
	cout << "***NOTE***\nThe origin of the graph is the top right\n\n" << endl;
	#endif
}

void Map::print_map(){
	cout << "Map Key\n**********\n(0)nothing\n(1)trap\n(2)wumpus\n(3)gold\n(4)bats\n**********" << endl;
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			cout << "[";
			game_map[j][i].output_top_room();
			cout << "] ";
		}
		cout << " " << endl;
	}
}

void Map::output_near(int x_coord, int y_coord){
	int show = 4, dir;
	int temp_x = x_coord;
	int temp_y = y_coord;
	#ifdef DEBUG
	if(x_coord > 0){
		cout << "\nLeft" << endl;
		game_map[temp_x - 1][temp_y].near();
	}
	if(x_coord < width - 1){
		cout << "Right" << endl;
		game_map[temp_x + 1][temp_y].near();
	}
	if(y_coord > 0){
		cout << "Up" << endl;
		game_map[temp_x][temp_y - 1].near();
	}
	if(y_coord < length - 1){
		cout << "Down" << endl;
		game_map[temp_x][temp_y + 1].near();
	}
	#endif
	#ifndef DEBUG
	dir = rand() % 4;
	while(show > 0){
		switch(dir){
			case 0:
				if(show == 0){
					break;
				}else{
					show = show - 1;
					if(x_coord > 0){
						game_map[temp_x - 1][temp_y].near();
					}
				}
			case 1:	
				if(show == 0){
					break;
				}else{
					show = show - 1;
					if(x_coord < width - 1){
						game_map[temp_x + 1][temp_y].near();
					}
				}
			case 2:	
				if(show == 0){
					break;
				}else{
					show = show - 1;
					if(y_coord > 0){
						game_map[temp_x][temp_y - 1].near();
					}
				}
			case 3:
				dir = 0;
				if(show == 0){
					break;
				}else{
					show = show - 1;
					if(y_coord < length - 1){
						game_map[temp_x][temp_y + 1].near();
					}
				}
		}
	}
	#endif
}

int Map::return_status(int x, int y){
	return game_map[x][y].get_top_event();
}

void Map::run_event(int x, int y, Player* cur_player){
//	cout << "Made it into map obj" << endl;
	game_map[x][y].run_event(cur_player);
}

int Map::out_width(){
	return width;
}

int Map::out_length(){
	return length;
}

void Map::check_event(int x, int y){
	game_map[x][y].near();
}

/*Map::~Map(){
	delete test_bat;
	delete test_pit;
	delete test_nothing;
	delete test_gold;
	delete test_wumpus;
	for(int i = 0; i < width; i++){
		delete game_map[i];
	}
	delete game_map;

}*/
