import turtle
import numbers


def main():
	start = True
	sides = 0
	sidesp = sides
	while start == True:
		start = False
		print("What shape do you want to make?");
		shape = str(input("1. triangle 2. square 3. hexagon 4. octagon: "));
		if ((shape.isdigit())==True):
			shape = int(shape);
			if shape == 1:
				sides = 3;
			if shape == 2:
				sides = 4;
			if shape == 3:
				sides = 6;
			if shape == 4:
				sides = 8;
			if shape<1:
				print("That is not a valid number");
				start = True;
			if shape>4:
				print("That is not a valid number");
				start = True;
		else:
			print("Your input needs to be an integer");
			start = True;
	sidesp = sides		
	window = turtle.Screen()
	turtle.setx(0);
	turtle.sety(0);
	while (sides>0):
		turtle.forward(15);
		turtle.right(360//sidesp);
		sides = (sides-1);
	window.mainloop();

main();
