choice = 1
while choice == 1:
  print("Choose an operation:")
  print("1. +")
  print("2. -")
  print("3. *")
  print("4. /")
  print("5. %")
  print("6. **")

  choice = -1
  while choice < 1 or choice > 6:
    choice = int(input())
  

  x = int(input("Enter first number:"))
  y = int(input("Enter second number:"))

  if choice == 1:
    print(x+y)
  elif choice == 2:
    print(x-y)
  elif choice == 3:
    print(x*y)
  elif choice == 4:
    print(x/y)
  elif choice == 5:
    print(x%y)
  elif choice == 6:
    print(x**y)

  choice = int(input("Enter 1 if you want to continuei:"))
