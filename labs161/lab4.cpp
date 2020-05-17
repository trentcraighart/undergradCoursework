#include <iostream>
using namespace std;
int main(){
	int x, y, num;
	string myanwser;
	string again;
	x = 3;
	y = x;
	cout << "X = 3" << endl;
	again = "1";
	while(again == "1"){
		cout << "Please input a number for Y: ";
		cin >> y;
		if(x < y){
			cout << "X is greater than Y" << endl;
			cout << "would you like to input another number? (1=yes)" << endl;
			cin >> again;
		}
		else{
			cout << "X is less than or equal to Y" << endl;
			cout << "would you like to input another number? (1=yes)" << endl;
			cin >> again;
		}
	}
	for (x = 0; x < 10; x++){
		cout << x << endl;
	}
	cout << "What number would you like to find the factorial for? ";
	cin >> num;
	
	int z;
	z = 1;
	
	for(x = 1; x <= num; x++){
		z = z * x;
		cout << z << endl;
	}
	
	cout << "Are you engoying cs161? (y or n) " << endl;
	cin >> myanwser;
	if(myanwser == "y"){
		cout << "YAY" << endl;
	}
	else{
		cout << "YOU WILL SOON!" << endl;
	}
	return 0;
}
