#ifndef rectangle_h
#define rectangle_h
#include "shape.h" 

using namespace std;

class Rectangle: public Shape{	
	private:
	float length;
	float width;
	public:
	Rectangle();
	void get_length();
	void get_width();
	void out_area();
};

#endif
