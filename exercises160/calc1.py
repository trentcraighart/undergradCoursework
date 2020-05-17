x = 1
while (x == 1):
  print("Enter a number operation (+, -, /, *, **, %):")
  o = input()

  print("Input your first number")
  f = int(input())

  print("Input your second number:")
  s = int(input())

  if o == '%':
    print(f % s)
  if o == '**':
    print(f ** s)
  if o == '*':
    print(f * s)
  if o == '/':
    print(f / s)
  if o == '-':
    print(f - s)
  if o == '+':
    print(f + s)

  print("Are you done? (no or yes)")
  answer = input()

  if answer == "yes":
    break
