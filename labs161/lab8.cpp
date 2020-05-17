#include <iostream>

#define PROMPT "Please enter a whole number:"
#define NOT_PRIME "The number is not a prime number.\n"
#define PRIME "The number is a prime number.\n"

using namespace std;

int is_prime(int);

int main(){
	int number; //number provided by the user

	cout << PROMPT; //prompt user
	cin >> number; //wait for input
	is_prime(number); // dertermine if number is prime

	return 0;
}

int is_prime(int number){
	for(int i = 2; i <= number/2; ++i){
		if(number%i == 0){
			cout << i << " Was divisible" << endl;
			cout << NOT_PRIME << number; //not prime
			return 0;
		}
		else{
			cout << i << " Was not divisible" << endl;
		}
	}
	cout << PRIME << number;
}
