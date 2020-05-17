#include <sys/time.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int fib_intr(int);
int fib_rec(int);


int main(){
	int amou1, amou2, n, val1 = 0, val2 = 1;
	typedef struct timeval time;
	time stop, start;
	cout << "Enter the fibonachi number: ";	
	cin >> n;

// iter
	gettimeofday(&start, NULL);
	amou1 = fib_intr(n);

	gettimeofday(&stop, NULL);

	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;

//recursive
	gettimeofday(&start, NULL);
	amou2 = fib_rec(n);

	gettimeofday(&stop, NULL);

	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;

	cout << amou1 << endl;
	cout << amou2 << endl;
	return 0;

}

int fib_intr(int n){

	int val1, val2, val3;
	val1 = 0, val2 = 1;
	for(n; n>1; --n){
		val3 = val1 + val2;
		val1 = val2;
		val2 = val3;
	}	
	return val3;	
}

int fib_rec(int n){
	if((n==1)||(n==0)){
		return n;
	}
	else{
		return fib_rec(n-1)+fib_rec(n-2);
	}
		
}
