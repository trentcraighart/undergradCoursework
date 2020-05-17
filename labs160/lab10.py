import numbers
def getinp():
	invalid = ("That input is invalid")
	start = 1
	while start==1:	
		bottles = str(input("How many bottles of grog do you have matey? "))	
		if ((bottles.isdigit())==True):
			bottles = int(bottles)
			if bottles > 0:
				return bottles
			else: 
				print(invalid)
		else: 
			print(invalid)

def count(bottles):
	while bottles>0:
		print(str(bottles)+" of grog on the wall, "+str(bottles)+" bottles of grog!")
		bottles = bottles-1
		print("Take one down drink it all down, "+str(bottles)+" of grog yo ho!")




def main():
	bottles = getinp()
	count(bottles)
	print("WHAT!?!?! That was our last bottle of grog! Time to get back to work ye land lubbers!")
main()
