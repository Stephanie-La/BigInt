/*****************************
Stephanie La
Novermber 2, 2019
******************************/

#include "BigInt.h"

int main() {
	BigInt x;
	cout << x << endl;
	x = BigInt(42);
	cout << x << endl;
	x = BigInt(" -123456789012345678901234567890 and more stuff");
	cout << x << endl;
	x = BigInt("+-4848484848484848");
	cout << x << endl;
	return 0;
}

BigInt::BigInt() {
	isNegative = false;
	data = "0";//format for a string
}

BigInt::BigInt(int x) {
	if (x < 0 ) {
		isNegative = true;
	}
	else {
		isNegative = false;
	}
	data = to_string(x);
}

BigInt::BigInt(string x) {
	string y;//for necessary input for what we need from x
	int i = 0;
	while (iswspace(x[i])) {
		i++;
	}
	if (x[i] == '-') {
		isNegative = true;
		y.insert(y.begin(), x[i]);
	}
	else if (x[i] == '+') {
		isNegative = false;
	}
	else if (isdigit(x[i])) {
		isNegative = false;
		y.insert(y.begin(), x[i]);
	}
	else {
		cout << "tried to construct an invalid BigInt from string:"<< endl;
		cout << x << endl;
		cout << "exiting";
		exit(1);
	}
	i++;

	while (!iswspace(x[i]) && x[i] != '\0')
	{
		if (isdigit(x[i])) {
			y.insert(y.end(), x[i]);
		}
		else {
			cout << "tried to construct an invalid BigInt from string:"<< endl;
			cout << x << endl;
			cout << "exiting";
			exit(1);
		}
		i++;
	}
	data = y;
}


ostream& operator<<(ostream& out, const BigInt& right) {
	return out << right.data;
}
