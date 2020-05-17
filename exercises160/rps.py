import numbers
Player1 = "Player1"
Player2 = "Player2"
def main():
  winner = None
  while winner == None:
    print("Rock, paper, scissors!")
    p1_choice = get_player_input(Player1)
    p2_choice = get_player_input(Player2)
    winner = determine_winner(p1_choice, p2_choice)
    if winner == None:
      print("It's a tie!")
  print("Player "+str(winner)+" won!")

#get_player_input function goes here
def get_player_input(name):
   x = 0
   start = 1
   while start==1:
      x = str(input(name+": 1 = Rock, 2 = Papaer, 3 = Scissors: "))
      if ((x.isdigit())==True):
         x = int(x)
         return x
         start = 0
      else:
         print("That is invalid")
#determine_winner function goes here
def determine_winner(x,y):
   if x != y:
      res = x - y
      if res == 1:
         return "Player 1"
      if res == -1:
         return "Player 2"
      if res == -2:
         return "PLayer 1"
      if res == 2:
         return "Player 2"

main()
