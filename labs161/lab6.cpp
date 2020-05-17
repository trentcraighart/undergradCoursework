#include <iostream>
#include <cstring>
using namespace std;

void palli(string);
void findreplace(string *);

int main(){
	int start;
	start = 1;
	do{
		string cat;
		cout << "Enter the string you are going to use:" << endl;
		getline(cin, cat);
		palli(cat);
		
	}
	while(start==1);



	return 0;
}

void palli(string cat){
	int i=0, cor=0;
	for(i=0; i < cat.length() ; i++){
		if(cat.at(i) == cat.at(cat.length()-i-1)){
			cor++;
		}
	}
	cout << cor << endl;
	if(cor==cat.length()){
		cout << "This is a Pallindrone" << endl;
	}		
}


