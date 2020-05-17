#include <iostream>
#include <string>
#include <cstdlib>
#include "lab1.h"

using namespace std;

int main(int argc, char** argv){
	int i, j, row, col;
	struct Table** sptr;
	row = atoi(argv[1]);
	col = atoi(argv[2]);
	

	sptr = new struct Table* [row];
	for(j=0;j<col;j++){
		sptr[j] = new struct Table[col]; 		
	}

	




	set_mult_values(sptr, row, col);





	
	cout << "\n";
	
	for(i=1;i<row+1;i++){
		cout << "\n";
		for(j=1;j<col+1;j++){
			sptr[i-1][j].div = float(i)/float(j);
			cout << sptr[i-1][j].div << " ";
		}
	}
	cout << "\n";
	return 0;

}

void set_mult_values(struct Table** sptr, int row, int col){	
	int i, j;
	for(i=1;i< row+1;i++){
		cout << "\n";
		for(j=1;j< col+1;j++){
			//struct Table sptr[i-1][j].mult = i*j;
			sptr[i-1][j].mult = i*j; 			
			cout << sptr[i-1][j].mult << " ";
		}
	}
}







