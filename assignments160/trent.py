import turtle
window = turtle.Screen();
def main(x,y):
	turtle.reset();
	head = 20
	turtle.setx(0);
	turtle.sety(0);
	turtle.setheading(0);
	#Makes a Head
	while (head>0):
		turtle.forward(2);
		turtle.left(18);
		head = (head-1);
	#Makes a Body
	turtle.goto(0,-10);
	turtle.goto(5,-8);
	turtle.goto(0,-10);
	turtle.goto(-5,-8);
	turtle.goto(0,-10);
	turtle.goto(0,-20);
	turtle.goto(5,-25);
	turtle.goto(0,-20);
	turtle.goto(-5,-25);
	#makes an H
	turtle.setx(30);
	turtle.sety(30);
	turtle.goto(30,20);
	turtle.goto(30,25);
	turtle.goto(25,25);
	turtle.goto(25,30);
	turtle.goto(25,20);
	#makes an i
	turtle.setx(35);
	turtle.sety(20);
	turtle.goto(35,25);
	turtle.setheading(270);
turtle.onclick(main);

window.mainloop();

