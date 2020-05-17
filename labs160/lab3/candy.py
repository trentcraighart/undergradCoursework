coop = int(input("How many coupons do you have to spend today? "));
message1 = "You have enough coupons to buy this many candy bars: ";
message2 = "You have enough coupons to buy this many gum balls: ";
pcan = coop
pgum = coop
pcan = pcan // 10
pgum = pgum // 3
print(str(message1)+str(pcan));
print(str(message2)+str(pgum));
cwant = pcan
if (pcan >= 1):
	while (cwant >= pcan):
		cwant = int(input("How many candy bars do you wish to buy? "));
coop = coop - cwant * 10
gwant = coop // 3
message3 = "With that many candy bars, you can still get this many gumballs: ";
print (str(message3)+str(gwant));


