#include "animal.cpp"
#include "tiger.cpp"
#include "bear.cpp"
#include "penguine.cpp"
#include "zoo.cpp"
#include "functions.cpp"
#include "high_score.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

int main(){
	srand(time(NULL));
	High_Score  game_hs;
	Zoo game_zoo;
	game_hs.print_score();
	for(int i = 0; i < 10; i++){
		cout << "\nDAY " << i+1 << "\n" << endl;
		buy_animal(&game_zoo);
		game_zoo.feed_animals();	
		game_zoo.profit_animals();
		game_zoo.random_event();
		game_zoo.inc_age();
	}
	game_hs.write_score(game_zoo.cur_money());
	return 0;
	


}

