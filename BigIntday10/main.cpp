#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;


int main() {
	int i;
	BigInt a("99999");
	BigInt b("1000");
	cout << b << "/" << a << endl << "= " << a / b << endl;


	a = BigInt("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
	b = BigInt("123");


	cout << a << "/" << b << endl << "= " << a / b << endl;


	/*
	a = BigInt("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
	b = BigInt("1");
	cout << " " << a << "+" << b << endl << "= " << a + b << endl;*/

	//cout << " " << a << "+" << b << endl << "= " << a + b << endl;
	/*cout << "Expecting 1, got: " << (BigInt("-30") < BigInt("-1")) << endl;
	cout << "Expecting 0, got: " << (BigInt("30") < BigInt("-1")) << endl;
	cout << "Expecting 1, got: " << (BigInt("30") < BigInt("300")) << endl;
	cout << "Expecting 0, got: " << (BigInt("-30") < BigInt("-300")) << endl;*/
	return 0;
}
