#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){

	int choice;

	srand (time(NULL));
	
	cout << "You wake up on a couch, the dim soft light falls from the window." << endl;
	cout << "As you look around you realise you're in an aincient mansion." << endl;
	cout << "You look at the table next to the couch and see a tomb with glyphs on the cover." << endl;
	cout << "Do you read the tomb? 1=yes 2=no " << endl;
	
	cin >> choice;
	switch(choice){

		case 1:
			cout << "You begin to read the tomb and your mind is brought to madness!" << endl;
			cout << "You fall to insanity and die..." << endl;
			cout << "The end" << endl;
			break;
		case 2:
			cout << "Probably a safe bet to avoid the tomb, good on you!" << endl;
			cout << "You proceede to look around the room and see a trap door!" << endl;
			cout << "Do you want to open it? 1=yes 2=no " << endl;
			cin >> choice;
			switch(choice){

				case 1:
					cout << "As you peak into the trap door, a tenticle grabs your arm and pulls you in!" << endl;
					cout << "The end" << endl;
					break;
				case 2:
					cout << "Probably another good plan, who knows what could be in there!" << endl;
					cout << "You see a door that leads out of the mansion and into the woods, what do you do? 1=leave 2=stay" << endl;
					cin >> choice;
					switch(choice){
						case 1: 
							cout << "You venture out into the woods and find a monster!" << endl;
							if (rand()%10 < 5){
								cout << "It's a WEREWOLF!" << endl;
							}else{
								cout << "It's a VAMPIRE!" << endl;
								cout << "Do you want to run?!? 1=yes 2=no " <<  endl;
							}
							cout << "Do you want to run?? 1=yes 2=no " << endl;
							cin >> choice;
							switch(choice){
								case 1:
									if (rand()%10 < 5){
										cout << "You get caught and eaten by the monster!" << endl;
										cout << "The end" << endl;
									}else{
										cout << "You escape the monster and run home! You survived!" << endl;
									}
									break;
								case 2:
									cout << "You don't run and befriend the monster instead!" << endl;
									cout << "The monster leads you back to civilization and is now your new best friend!" << endl;
									cout << "The end" << endl;
									break;
							break;
							}
							break;	
						case 2:
							cout << "You decide everything is too scary in this story and sit on the couch." << endl;
							cout << "You sit there untill everthing is over and the story is done..." << endl;
							cout << "The end" << endl;
							break;
					}
			}
	}
}
