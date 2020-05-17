#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//Prototypes
int count_letters(char **);
void output_letters(int num, char **);

int main(int argc, char *argv[]){
	int num;
	num = count_letters(argv);
	output_letters(num, argv);	
	
}

int count_letters(char **argv){
	int num, it;
	string line;
	char c;
	ifstream myfile(argv[1]);
	if(myfile.is_open()){
		while(getline(myfile,line)){
			for(it = 0;it < line.length(); it++ ){
				if(line.at(it) == 'f' || line.at(it) == 'F'){
					num++;
				}
			}
		}
						

	}else{
		cout << "file didn't open" << endl;
		return 0;
	}
	cout << " number of f is " << num << endl;
	myfile.close();
	return num;
}

void output_letters(int num, char **argv){
	ofstream myfile(argv[2]);
	if(myfile.is_open()){
		myfile << "The number of 'f' is " << num << endl;
		
	}
	myfile.close();


}
