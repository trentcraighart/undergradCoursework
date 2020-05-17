#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
	int num1, num2, num3;

	for(int i = 0; i < 10; i++){
		num1 = i;
		num2 = i + 1;
		num3 = i * i+1;
	}
	cout << "Begining of program" << endl;

	#ifdef DEBUG
	cout << num1 << endl;
	cout << num2 << endl;
	cout << num3 << endl;
	cout << "End of DEBUG" << endl;
	#endif
	cout << "End of program" << endl;

	return 0;

}
