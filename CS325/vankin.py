import copy
import sys
import time

def main():
	start_time = time.time()
	"""this fixes the problem with python only allowing 995 elements on the stack"""
	sys.setrecursionlimit(2048);
	"""The globals are to ease the access of finding data"""
	global matrix
	global dimension
	global cur_top
	global value_matrix
	global tested_matrix
	matrix = []
	dimension = []
	cur_top = []
	value_matrix = []
	tested_matrix = []
	build()
	value_matrix = copy.deepcopy(matrix)
	cur_top.append(-100)
	recurse(0, 0, 0, 0)
	output();
	print("--- %s seconds ---" % (time.time() - start_time))

def output():
	"""Clears file"""
	open("output.txt", "w").close()
	"""Writes the top to the file"""
	f = open("output.txt", "w")
	f.write(str(cur_top[0]))
	print(cur_top[0])

def build():
	i = 0;
	first_list = [];
	f = open("input.txt");	
	"""reads teh first value, the dimension into the global"""
	dimension.append(f.readline());
	amount_per_list = (int(dimension[0]) - 1)
	while(i <= int(dimension[0]) - 1):
		second_list = [];
		"""this breaks each element of the list by the comas"""
		second_list = f.readline().split(",");
		"""removes the \n from the files"""
		temp_val = second_list[amount_per_list].replace("\n", "");
		second_list[amount_per_list] = temp_val;
		i = i + 1;
		matrix.append(second_list)
	"""This ill construct the test list so we know if an elements has been visited"""
	i = 0
	while(i < int(dimension[0])):

		j = 0
		init_list = []
		while(j < int(dimension[0])):
			init_list.append(0)
			j = j + 1
		tested_matrix.append(init_list)
		i = i + 1

def recurse(x, y, prev_x, prev_y):
	"""***NOTE RIGHT = DOWN***"""
	"""This function will go through from the top left and find the largest path for solitare"""
	"""initialize variables"""
	right_path = 0
	left_path = 0
	runing_total = int(value_matrix[prev_x][prev_y])
	current_node = int(matrix[x][y])
	width = int(dimension[0])
	"""Checks if its already preforemed recursion"""
	if(int(tested_matrix[x][y]) == 0):
		if(x < width - 1):
			right_path = recurse(x+1, y, x, y)
		if(y < width - 1):
			left_path = recurse(x, y+1, x, y)
		"""Compares resualts from both left and bottom path"""
		if(right_path > left_path):
			new_val = int(matrix[x][y]) + right_path
			value_matrix[x][y] = new_val
			"""marks an element as visited"""
			tested_matrix[x][y] = 1
			"""Checks if the value is the new largest value"""
			if(new_val > int(cur_top[0])):
				cur_top.pop()
				cur_top.append(new_val)
			return new_val
		else:
			new_val = int(matrix[x][y]) + left_path
			value_matrix[x][y] = new_val
			"""marks elements as visited"""
			tested_matrix[x][y] = 1
			"""Checks if the value is the new largest value"""
			if(new_val > int(cur_top[0])):
				cur_top.pop()
				cur_top.append(new_val)
			return new_val

	else:
		"""We already set value_matrix aproprietly"""
		return value_matrix[x][y];

main();	
