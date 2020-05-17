#include <iostream>

using namespace std;

void towers(int disks, int b[][3], int from_col, int to_col, int spare){
	
	if(disks == 0){
		b[spare][to_col] = b[spare][from_col];
		cout << b[0][0] << b[0][1] << b[0][2] << endl;
		cout << b[1][0] << b[1][1] << b[1][2] << endl;

		

	}else{
	
		towers(disks - 1, b, from_col, spare, to_col);
	

		towers(disks - 1, b, spare, to_col, from_col);
	}
}


main(){
	
	int b[3][3];
	b[0][0] = 1;
	b[0][1] = 2;
	
	towers(3, b, 1, 2, 3);





}
