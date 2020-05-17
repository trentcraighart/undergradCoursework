#include "functions.h"

int get_int(){
	int i, valuef, test = 0, start = 1;
	string value;
	while(start == 1){
		test = 0;
		cin >> value;
		for(int i = 0; i < value.size(); i++){
			if(value[i]<=57 && value[i]>=48){
				test += 1;
			}else{
				cout << "invalid input, new input:";
			}
			if(test==value.size()){
				start = 0;
			}
		}
	}
	valuef = atoi(value.c_str());
	return valuef;
}

//Template
/***
 * Function:
 * Description:
 * Parameters:
 * Pre_Conditions:
 * Post_Conditions:
***/
