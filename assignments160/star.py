import turtle
window = turtle.Screen();
def main(x,y):
	turtle.reset();
	move = 5;
	turtle.setx(0);
	turtle.sety(0);
	turtle.setheading(90);
	while (move>0):
		turtle.forward(30);
		turtle.left(144);
		move = (move-1);


turtle.onclick(main);

window.mainloop();

