import math;
import numbers;
start = 1
message1 = 'Perfect Square ';
message2 = 'Here is my squareroot aproximation for you '
message3 = 'Here is the anwser '
message4 = 'Here is the math modules anwser '
while (start==1):
	test = 0
	test2 = 1
	star = int(input("Enter a number to squar root : "));
	while (test2 > 0):
		test = (test + 1);
		test2 = test
		test2 = (test2 ** 2);
		test2 = (star - test2);
	if (test2==0):
		print(str(message1)+str(test));
	elif (test2!=0):	
		test = (test - 1);
		test2 = 1
		while (test2 > 0):
			test = (test + 0.1);
			test2 = test
			test2 = (test2 ** 2);
			test2 = (star - test2);
		if (test2==0):
			print(str(message3)+str(test));
		elif (test2!=0):
			test = (test - 0.1);
			test2 = 1
			while (test2 > 0):
				test = (test + 0.01);
				test2 = test
				test2 = (test2 ** 2);
				test2 = (star - test2);
			if (test2==0):
				print(str(message3)+str(test));
			elif (test2!=0):
				test = (test - 0.01);
				modual = math.sqrt(star);
				print(str(message2)+str(test));
				print(str(message4)+str(modual));




			
		
		
		
		

