#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;


int test_string();
main(){
	srand(time(0));
	cout << "Welcome to Password Generator!" << endl;
	int leng, prup, prlo, prnu, prsp, run, v1, v2, i;
	string value;
	prup = 0, prlo = 0, prnu = 0, prsp = 0;
	leng = 0;
	run = 0;
	v1 = 0;
	v2 = 0;
	do
	{
		cout << "How long do you want the password to be? ";
		leng = test_string();
	}	while(leng < 1);

	cout << "What precent of your password do you want uppercase? (if none enter 0) ";
	prup = test_string();
	cout << "What precent of your password do you want lowwercase? (if none enter 0) ";
	prlo = test_string();
	cout << "What precent of your program do you want as numbers? (if none enter 0) ";
	prnu = test_string();
	cout << "The remaing precentage out of 100 will be allocated to special characters ";
	prsp = 100-prup-prlo-prnu;
	cout << prsp << endl;
	for(leng; leng > 1; --leng){
		v1 = rand() % 100;
		if(v1 < prup){
			v2 = rand() %26 + 65;
			cout << char(v2);
		}
		else{
			v1 = rand() % 100;
			if(v1 < prlo){
				v2 = rand() %26 + 97;
				cout << char(v2);
			}
			else{
				v1 = rand() % 100;
				if(v1 < prnu){
					v2 = rand() %  10;
					cout << int(v2);
				}
				else{	
					if(prsp > 0){
						v2 = rand() %10 + 33;
						cout << char(v2);
					}
				}
			}
		}
	}
	
	



	cout << " Do you want to run the program again (1-yes)? ";
	cin >> run;
	if(run == 1){
		main();
		}
	else{
		cout << "Thanks for using the password generator! " << endl;
	}
}
//Description: Checks if the string is an int
//Return: an integer
int test_string(){
	int i, test, valuef;
	bool start;
	test = 0;
	start = true;
	string value;
	while(start==true){
		test = 0;
		cin >> value;
		for(int i = 0; i < value.size(); i++){
			if(value[i]<=57 && value[i]>=48){
				cout << "valid" << endl;
				test += 1;
			}
			else{
				cout << "invalid" << endl;
			}
			if(test==value.size()){
				start = false;
			}
		}
	}
	valuef = atoi(value.c_str());
	return valuef;	
}

