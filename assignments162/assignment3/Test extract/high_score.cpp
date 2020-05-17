#include "high_score.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

void High_Score::print_score(){
	string line;
	ifstream myfile("high_score_table.txt");
	if(myfile.is_open()){
		while(getline(myfile,line)){
			stringstream convert(line);
			convert >> score;

			cout << "For 10 days, the high score is : " << score << endl;
		}
		myfile.close();
	}else{
		cout << "Unable to open high score table" << endl;
	}	
}

void High_Score::write_score(int new_score){
	string line;
	ofstream myfile("high_score_table.txt");
	if(myfile.is_open()){
		if(new_score > score){
			myfile << new_score;
			cout << "NEW HIGH SCORE: " << new_score << endl;
			cout << "OLD HIGH SCORE: " << score << endl;
		}else{
			cout << "No new high score" << endl;
			cout << "CURRENT HIGH SCORE: " << score << endl;
			cout << "YOUR SCORE: " << new_score << endl;
		}
		myfile.close();
	}else{
		cout << "Unable to open high score table" << endl;
	}
}
