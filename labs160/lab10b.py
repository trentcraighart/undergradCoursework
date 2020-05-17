cat = str(raw_input("Enter input "))
list(cat)
parrr = 0
for ch in cat:
	if ch == '(':
		parrr += 1
	if ch == ')':
		parrr -= 1
	if parrr < 0:
		print("not valid");
if parrr == 0:
	print("may be valid")
else: print("not valid")
