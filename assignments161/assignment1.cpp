#include <iostream>
#include <cmath> 
#include <math.h>
#include <climits>
using namespace std;
int main(){

	cout << "cos(2pi/3)=" << cos(2*M_PI/3) << endl;
	cout << "2sin(2pi/3)=" << 2*sin(2*M_PI/3) << endl;
	cout << "tan(-3pi/4)=" << tan(-3*M_PI/4) << endl;
	cout << "log(55)=" << log10(55) << endl;
	cout << "ln 60=" << log(60) << endl;

	cout << "logsub2(15)=" << (log(15))/(log(2)) << endl;
	cout << "logsub4(40)=" << (log(40))/(log(4)) << endl;

	cout << "3^(sinx)" << endl;
	cout << "x1=" << pow (3,(sin(1))) << endl;
	cout << "x10=" << pow (3,(sin(10))) << endl;
	cout << "x100=" << pow (3,(sin(100))) << endl;
	
	cout << "logsub2(x^(2)+1)" << endl;
	cout << "x1=" << (log(1+1))/(log(2)) << endl;
	cout << "x10=" << (log(100+1))/(log(2)) << endl;
	cout << "x100=" << (log(1000+1))/(log(2)) << endl;

	cout << "Math is fun!" << endl;

	cout << "Minimum value signed character " << SCHAR_MIN << endl;
	cout << -(pow (2,7)) << endl;
	cout << "Maximum value signed character " << SCHAR_MAX << endl;
	cout << (pow (2,7))-1 << endl;
	cout << "Maximum value unsigned character " << UCHAR_MAX << endl;
	cout << (pow (2,8))+1 << endl;

	cout << "Minimum value short int " << SHRT_MIN << endl;
	cout << -(pow (2,15)) << endl;
	cout << "Maximum value short int " << SHRT_MAX << endl;
	cout << (pow (2,15))-1 << endl;
	cout << "Minimum value unsigned short int " << USHRT_MAX << endl;
	cout << (pow (2,16))-1 << endl;

	cout << "Minimum value long int " << LONG_MIN << endl;
	cout << -(pow (2,31)) << endl;
	cout << "Maximum value long int " << LONG_MAX << endl;
	cout << (pow (2,31))-1 << endl;
	cout << "Maximum value unsigned long int " << ULONG_MAX << endl;
	cout << (pow (2,32))-1 << endl;

	return 0;

}
