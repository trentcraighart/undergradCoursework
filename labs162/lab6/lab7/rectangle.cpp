#include "rectangle.h"

Rectangle::Rectangle(){
	length = 1.0;
	width = 1.0;
	name = "Rectangle";
}

void Rectangle::get_length(){
	cout << "Input length for " << name << ": ";
	cin >> length;
}
void Rectangle::get_width(){
	cout << "Input width for " << name << ": ";
	cin >> width;
}

void Rectangle::out_area(){
	cout << "Input width for " << name << ": ";
	cin >> width;
	cout << "Input length for " << name << ": ";
	cin >> length;
	cout << "Area for " << name << ": " << (width * length) << endl;
}
