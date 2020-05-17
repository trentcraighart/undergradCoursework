#include "circle.cpp"
#include "rectangle.cpp"
#include "shape.cpp"

//Prototypes
void print_shape_info(Shape*);

using namespace std;

int main(){
	Circle cir1;
	Rectangle rect1;

	Shape * shape1 = &rect1;
	Shape * shape2 = &cir1;

	shape1->out_area();
	shape1->set_color();
	shape1->set_name();	

	shape2->out_area();
	shape2->set_color();
	shape2->set_name();

	print_shape_info(shape1);
	print_shape_info(shape2);
	
	return 0;
}

void print_shape_info(Shape *the_shape){
	the_shape->out_color();
	the_shape->out_name();
//	the_shape.out_area();
}
