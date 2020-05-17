import random
import string
import sys

def main():
	makeFiles();
	readFiles();
	math();

def math():
	"""takes two random ints between 1 and 42, prints them on indiv lines, then mults and prints"""
	i = random.randint(1, 42)
	print(i)
	j = random.randint(1, 42)
	print(j)
	print(i*j)

def makeFiles():
	"""initialize and clear previous files"""
	files = []
	files.append("file1.txt")
	files.append("file2.txt")
	files.append("file3.txt")
	for i in range (0, 3):
		open(files[i], "w").close()
	"""adding 8 random chars to files ending with \n"""
	for i in range (0, 3):
		f = open(files[i], "w")
		for j in range(0, 10):
			f.write(random.choice(string.ascii_lowercase))
		f.write("\n")
		f.close();


def readFiles():
	files = []
	files.append("file1.txt")
	files.append("file2.txt")
	files.append("file3.txt")
	"""read each file, print contents to string without print()'s newline"""
	for i in range(0, 3):
		f = open(files[i], "r")
		sys.stdout.write(f.read())
		sys.stdout.flush()

main();