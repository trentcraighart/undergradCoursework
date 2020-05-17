import numbers
nmass1 = "mass1 "
nmass2 = "mass2 "
ndist = "distance "
mass1 = 0
mass2 = 0
dist = 0


def getinput(nam):
	start = 1
	var = 0
	while start == 1:
		var = str(input(nam))
		if ((var.isdigit())==True):
			var = int(var)
			start = 0
			return var
		else:
			print("invalid input")

def get_gravitational_force(mass1, mass2, dist):
	anw = (mass1*mass2*6.673)
	anw = (anw/dist)
	print("Your gravitational force is "+str(anw)+" X 10^-8")

def restart():
	anw = str(input("If you want to use the program again, please enter 'yes' "))
	if anw == "yes":
		main()


def main():
	nmass1 = "mass1 "
	nmass2 = "mass2 "
	ndist = "distance "
	mass1 = 0
	mass2 = 0
	dist = 0

	mass1 = getinput(nmass1)
	mass2 = getinput(nmass2)
	dist = getinput(ndist)
	get_gravitational_force(mass1, mass2, dist)
	restart()
main()
