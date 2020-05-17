#ifndef shape_h
#define shape_h
#include <string>
#include <cstdlib>

using namespace std;

class Shape{
	protected:
//	private:
	string color;
	string name;
	public:
	Shape();
	void set_color();
	void set_name();
	void out_color();
	void out_name();
	virtual void out_area() = 0;
};

#endif
