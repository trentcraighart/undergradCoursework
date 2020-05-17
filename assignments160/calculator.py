select = 1
start = 'y'
cookie = 1
print("Hello and welcome to my calculator!");
print("Note, this calculator only works with whole numbers");
print("Please refrain from using any 'words'");
while (start == 'y'):
	while (cookie == 1):
		opp = str(input("Imput Operand: + - / * % **: "));
		if opp == '+':
			cookie = 0
		elif opp == '-':
			cookie = 0
		elif opp == '/':
			cookie = 0
		elif opp == '*':
			cookie = 0
		elif opp == '%':
			cookie = 0
		elif opp == '**':
			cookie = 0
		elif opp == 'Wake up Neo':
			print("follow the white rabbit");
		elif opp == 'words':
			print("You know what you've done :p");
	num1 = int(input("What is your first number: "));
	num2 = int(input("What is your second number: "));
	if opp == '+':
		print(num1 + num2);
	elif opp == '-':
		print(num1 - num2);
	elif opp == '/':
		print(num1 / num2);
	elif opp == '*':
		print(num1 * num2);
	elif opp == '**':
		print(num1 ** num2);
	elif opp == '%':
		print(num1 % num2);
	cookie = 1; 
	start = str(input("Press y to contineu, any other key to quit "));
print("Thanks for using my calculator!");

