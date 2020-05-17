#include "shape.h"

Shape::Shape(){
	color = "none";
	name = "none";
}

void Shape::set_color(){
	cout << "Input color: ";
	cin >> color;
}

void Shape::set_name(){
	cout << "Input name: ";
	cin >> name;
}

void Shape::out_color(){
	cout << color << endl;
}

void Shape::out_name(){
	cout << name << endl;
}

//void out_area(){
//	cout << "Nothing" << endl;
//}
