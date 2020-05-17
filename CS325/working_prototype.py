def main():
	matrix = []
	dimension = []
	build(dimension, matrix)
	print(matrix)
	best_value = recurse(0, 0, int(dimension[0]), matrix)
	print(best_value)

def build(dimension, matrix):
	i = 0;
	first_list = [];
	f = open("input.txt");	
	dimension.append(f.readline());
	amount_per_list = (int(dimension[0]) - 1)
	while(i <= int(dimension[0]) - 1):
		second_list = [];
		second_list = f.readline().split(",");
		temp_val = second_list[amount_per_list].replace("\n", "");
		second_list[amount_per_list] = temp_val;
		i = i + 1;
		matrix.append(second_list)

def recurse(x, y, dimension, matrix):
	if(x < dimension - 1):
		right_path = recurse(x + 1, y, dimension, matrix)
	else:
		right_path = 0;
	if(y < dimension - 1):
		left_path = recurse(x, y + 1, dimension, matrix)
	else:
		left_path = 0
	if(right_path > left_path):
		return right_path + int(matrix[x][y])
	else:
		return left_path + int(matrix[x][y])

main();	