#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;

int main()
{
	BigInt a("100");
	BigInt b("100");
	cout << a << " * " << b << endl
		<< "Expecting 10000 got" << endl
		<< " " << a * b << endl;
	cout << endl;
	a = BigInt("1234");
	b = BigInt("-678");
	cout << a << " * " << b << endl
		<< "Expecting -836652 got" << endl
		<< " " << a * b << endl;
	cout << endl;
	a = BigInt("-123456789012345678901234567890");
	b = BigInt("-987654321");
	cout << a << " * " << b << endl
		<< "Expecting 121932631124828532112482853211126352690 got" << endl
		<< " " << a * b << endl;
	return 0;
}
