import turtle
def main():
	sides = int(input("How many sides do you want? "));
	sidesp = sides
	window = turtle.Screen()
	my_turtle = turtle.Turtle()
	turtle.setx(0);
	turtle.sety(0);
	while (sides>0):
		turtle.forward(15);
		turtle.right(360//sidesp);
		sides = (sides-1);
	window.mainloop();
main()
