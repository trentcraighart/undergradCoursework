#include <iostream>
#include <cstdlib>

using namespace std;

class cat{
	private:
	int fat;
	int* arr;
	public:
	cat();
	void inc_fat();
	void out_fat();
	void set_zero();
	void out_zero();
	~cat();
};

class dog{
	private:
	int pup;
	public:
	dog();
};

cat::cat(){
	fat = 3;
	arr = new int[5];
}

void cat::inc_fat(){
	fat++;
}

void cat::out_fat(){
	cout << fat << endl;
}

void cat::set_zero(){
	arr[0] = 2;
}

void cat::out_zero(){
	cout << arr[0] << endl;
}

cat::~cat(){
	delete [] arr;
	cout << "Detleted" << endl;
}

dog::dog(){
	int pup = 2;
}




int main(){

	#ifdef EXE1
	cat* kitty;
	kitty = new cat[3];
	cout << "Cat Location 2" << endl;
	kitty[2].out_fat();
	cout << "Cat Location 3" << endl;
	kitty[3].out_fat();
	#endif

	#ifdef EXE2
	cat milo;
	dog otis;
	otis.inc_fat();
	#endif

	#ifdef EXE3
	cat cat1, cat2;
	cat2 = cat1;
	cat1.set_zero();
	cat2 = cat1;
	cat1.out_zero();
	cat2.out_zero();
	#endif

	#ifdef EXE4
	cat* kitty;
	kitty[3].inc_fat();
	kitty[3].out_fat();
	#endif
	
	cout << "End of program" << endl;

	return 0;
		
}
