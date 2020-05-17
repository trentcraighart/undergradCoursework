radi = int(input("Radius in feet: "));
weig = int(input("Weight in pounds: "));
buoy = (((4/3)*3.14*(radi**3))*62.4);
message1 = 'Buoyant force ';
print(str(message1)+str(buoy));
if (buoy >= weig):
	print("This sphere will float");
else:
	print("This sphere will sink");
