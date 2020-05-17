#include <iostream>
#include <string>
using namespace std;

void get_sentence(string &s);

int main(){
	string sent;

	get_sentence(sent);
	
	cout << sent << endl;
	
	return 0;
}

void get_sentence(string &s){
	getline(cin, s);
}
