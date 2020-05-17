#ifndef circle_h
#define circle_h
#include "shape.h"

using namespace std;

class Circle: public Shape{
	private:
	float radius;
	float pi;	
	public:
	Circle();
	void get_radius();
	void out_area();
};

#endif
