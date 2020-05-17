#include "circle.h"
#include <cstdlib>
#include <iostream>

Circle::Circle(){
	radius = 1.0;
	pi = 3.14;
	name = "Circle";
}

void Circle::get_radius(){
	cout << "Input radius for " << name << ": ";
	cin >> radius;
}

void Circle::out_area(){
	cout << "Input radius for " << name << ": ";
	cin >> radius;
	cout << "Area for " << name << ": " << ((radius * radius) * pi) << endl;
}
