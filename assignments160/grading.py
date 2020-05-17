import numbers
#Here are some strings I will be using frequently
test = "tests"
asig = "asignments"
labs = "labs"
exer = "exercises"
fina = "final"

print("Hello and thank you for using my program!");
print("Questions labled with *** require input in the following, yes = 1, no = 0");

#exi = exist amo = amount pre = precent
def main():
   start = "1"
   while start == "1":

      testexi = get_inp_exi(test);
      testpre = get_inp_pre(test,testexi);
      testamo = get_inp_amo(test,testexi);
      testtot = get_inp_tot(test,testexi,testamo);
      testpoi = get_inp_poi(test,testexi,testamo);
      testest = calc_pre(testpoi,testtot,testpre,testexi);

      asigexi = get_inp_exi(asig);
      asigpre = get_inp_pre(asig,asigexi);
      asigamo = get_inp_amo(asig,asigexi);
      asigtot = get_inp_tot(asig,asigexi,asigamo);
      asigpoi = get_inp_poi(asig,asigexi,asigamo);
      asigest = calc_pre(asigpoi,asigtot,asigpre,asigexi);
      
      labsexi = get_inp_exi(labs);
      labspre = get_inp_pre(labs,labsexi);
      labsamo = get_inp_amo(labs,labsexi);
      labstot = get_inp_tot(labs,labsexi,labsamo);
      labspoi = get_inp_poi(labs,labsexi,labsamo);
      labsest = calc_pre(labspoi,labstot,labspre,labsexi);

      exerexi = get_inp_exi(exer);
      exerpre = get_inp_pre(exer,exerexi);
      exeramo = get_inp_amo(exer,exerexi);
      exertot = get_inp_tot(exer,exerexi,exeramo);
      exerpoi = get_inp_poi(exer,exerexi,exeramo);
      exerest = calc_pre(exerpoi,exertot,exerpre,exerexi);
      
      finaexi = get_inp_exi(fina);
      finapre = get_inp_pre(fina,finaexi);
      finaamo = get_inp_amo(fina,finaexi);
      finatot = get_inp_tot(fina,finaexi,finaamo);
      finapoi = get_inp_poi(fina,finaexi,finaamo);
      finaest = calc_pre(finapoi,finatot,finapre,finaexi);

      final_pre(testpre,asigpre,labspre,exerpre,finapre);
      final_calc(testest,asigest,labsest,exerest,finaest);
      
      start = str(input("If you want to use the program again enter 1, anything else to quit "))

def get_inp_exi(name):
   start = True
   work = 2
   while start == 1:
      work = str(input("*** Will "+name+" be in this class? "));
      if work == '1':
         return True
         start = False
      if work  == '0':
         return False
         start = False

def get_inp_amo(name,true):
   if true == True:
      start = True
      while start == True:    
         amo = str(input("For "+name+" how many items do you have to grade? "));
         if ((amo.isdigit())==True):
            amo = int(amo)
            return (amo)
            start = False
         else:
            print("That is invalid input");
   else:
      return 0

def get_inp_pre(name,true):
   if true == True:
      start = True
      while start == True:
         pre = str(input("What precentage of the class are "+name+" worth? "));
         if ((pre.isdigit())==True):
            pre = int(pre)
            return pre
         else:
            print("That is invalid input");
   else:
      return 0

def get_inp_tot(name,true,amo):
   if true == True:
      kno = 0
      tot = 0
      numb = 0
      step = True
      start = True
      while start == True:
         kno = str(input("*** Do you know the total points for "+name+"? "));
         while kno == '1':
            tot = str(input("What is the total points for "+name+"? "));
            if ((tot.isdigit())==True):
               tot = int(tot)
               if tot > 0:
                  return (tot)
                  start = False
                  kno = 2
               else:
                  print("That is invalid input");
            else:
               print("That is invalid input");
         while kno == '0':
            while numb<amo:
               if step==True:
                  numb = numb+1
                  step = False
               sco = str(input("Enter TOTAL amount of points for the "+str(numb)+" "+name+": "));
               if ((sco.isdigit())==True):
                  sco = int(sco)
                  if tot > 0:
                     tot = tot + sco
                     step = True
                  else:
                     print("That is not valid input")  
               else:
                  print("That is not valid input")
            else:
               start = False
               return tot
                     
def get_inp_poi(name,true,amo):
   if true == True:
      kno = 0
      tot = 0
      numb = 0
      step = True
      start = True
      while start == True:
         kno = str(input("*** Do you know the total points the student scored for "+name+"? "));
         while kno == '1':
            tot = str(input("What are the total points the student scored "+name+"? "));
            if ((tot.isdigit())==True):
               tot = int(tot)
               return (tot)
               start = False
               kno = 2
            else:
               print("That is invalid input");
         while kno == '0':
            while numb<amo:
               if step==True:
                  numb = numb+1
                  step = False
               sco = str(input("Enter TOTAL amount of points for the "+str(numb)+" "+name+" that the students scored: "));
               if ((sco.isdigit())==True):
                  sco = int(sco)
                  tot = tot + sco
                  step = True
               else:
                  print("That is not valid input")  
            else:
               start = False
               return tot

def calc_pre(poi,tot,pre,true):
   if true == True:
      final = 0
      final = (poi/tot)*(pre/100)*100
      return final
   else:
      return 0

def final_pre(pre1,pre2,pre3,pre4,pre5):
   final = (pre1+pre2+pre3+pre4+pre5);
   if final != 100:
      print("This class does not equal 100% The final result may not be accurate")

def final_calc(sco1,sco2,sco3,sco4,sco5):
   final = (sco1+sco2+sco3+sco4+sco5)
   if final < 100:
      if final < 90:
         if final < 80:
            if final < 70:
               if final < 60:
                  print("You recived a F at "+str(final)+"%")
               else:
                  print("You recived a D at "+str(final)+"%")
            else:
               print("You recived a C at "+str(final)+"%")
         else:
            print("You recived a B at "+str(final)+"%")
      else:
         print("You recived a A at "+str(final)+"%")
   else:
      print("You recived a A+ at "+str(final)+"%")

main();
