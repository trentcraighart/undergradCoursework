import numbers
#Here are some strings I will be using frequently
test = "tests"
asig = "asignments"
labs = "labs"
exer = "exercises"
fina = "final"
testnum = 0
testpre = 0
testtot = 0
testpoi = 0
asignum = 0
asigpre = 0
asigtot = 0
asigpoi = 0
labsnum = 0
labspre = 0
labstot = 0
labspoi = 0
exernum = 0
exerpre = 0
exertot = 0
exerpoi = 0
finanum = 0
finapre = 0
finatot = 0
finapoi = 0

print("Hello and thank you for using my program!");
print("For any instance in the program asking for a yes or no anwser, yes = 1, no = 0");


def main():
	get_input(test, testnum, testpre);
	get_input(asig, asignum, asigpre);
	get_input(labs, labsnum, labspre);
	get_input(exer, exernum, exerpre);
	get_input(fina, finanum, finapre);
	get_input_s(test, testnum, testpre, testtot, testpoi);
	get_input_s(asig, asignum, asigpre, asigtot, asigpoi);
	get_input_s(labs, labsnum, labspre, labstot, labspoi);
	get_input_s(exer, exernum, exerpre, exertot, exerpoi);
	get_input_s(fina, finanum, finapre, finatot, finapoi);
def get_input(name,numb,prec):
   start = True
   work = 2
   while start == 1:
      work = str(input("Will "+name+" be in this class? "));
      if work == '1':
         numb = str(input("How many of "+name+" will there be? "));
         if ((numb.isdigit())==True):
            numb = int(numb);
            prec = str(input("What precent is "+name+"worth? (Please only integers) "))
            if ((prec.isdigit())==True):
               prec = int(prec);
               start = False
            else:
               print("That is not valid input")
         else:
            print("That is not valid input")
      if work  == '0':
         	start = False


def get_input_s(name,numb,prec,tota,poin):
   start = True
   step = True
   print("In the catagory "+name+", you have this many items to grade:")
   print(numb);
   curnumb = 0
   while (curnumb<numb):
      if step == True:
         curnumb = curnumb + 1
      curpoin = 0
      curpoin = str(input("For assignment "+curnumb+" how many points did the student score? "))
      if ((curpoin.isdigit())==True):
         curpoin = int(curpoin)
         poin = poin + curpoin
         totpoin = 0
         totpoin = str(input("For assignment "+curnumb+" how many points was it worth total? "))
         if ((totpoin.isdigit())==True):
            totpoin = int(totpoin)
            tota = tota + totpoin
            step = True
         else:
            step = False
            print("That is not valid input")
      else:
         step = False
         print("That is not valid input")

main();
