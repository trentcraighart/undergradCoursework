import random

def main():
	input_val = input("Enter dimension of matrix: ")
	"""clears the previos data"""
	open("input.txt", "w").close()
	f = open("input.txt", "w")
	f.write(str(input_val) + "\n")
	"""i iterates by line, j by character"""
	i = 0;
	while(i < int(input_val)):
		j = 0
		while(j < int(input_val)):
			random_var = random.randint(-100,100);
			f.write(str(random_var))
			"""This will determine if its at the end of the line, if so it will \n, otherise ,"""
			if(j != int(input_val) - 1):
				f.write(',')
			else:
				f.write('\n')
			j = j + 1
		i = i + 1


main();
