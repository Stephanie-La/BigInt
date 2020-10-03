#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;

BigInt::BigInt() {
	isNegative = false;
	data = "0";//format for a string
}

BigInt::BigInt(int x) {
	if (x < 0) {
		isNegative = true;
	}
	else {
		isNegative = false;
	}
	data = to_string(abs(x));//storing it forwards 
}

BigInt::BigInt(string x) {
	int i = 0;
	isNegative = false;
	while (i < x.size()) { // while the whole loop is in bounds
		while (isspace(x[i])) { //while there is a space, skip over it
			i++;
		}
		if (x[i] == '-') { // check for an optinal sign
			isNegative = true;
			i++;
		}
		else if(x[i] == '+'){
			isNegative = false;
			i++;
		}
		while (isdigit(x[i])) { // while it is a number 
			if (x[i] == '0' && data.size() == 0) { //if it starts with a zero AND there's nothing in the string, skip
				i++;
			}
		else {
				data.push_back(x[i]); //otherwise add it to the stack, from the end so 123-> 1-> 12->123
				i++;
			}
		}
		if (!isdigit(x[i]) && data.size() == 0) {
			cout << "tried to construct an invalid BigInt from string:" << endl;
			cout << x << endl;
			cout << "exiting";
			exit(1);
		}
	}	
}

ostream& operator<<(ostream& out, const BigInt& right) {
	int i;
	if (right.data == "0") {
		return out << 0;//print a zero
	}
	else {
		if (right.isNegative) {
			out << '-';
		}
	}
	return out << right.data;
}

bool operator<(const BigInt& left, const BigInt& right) {
	if (left.isNegative != right.isNegative) {
		return left.isNegative;
	}
	else if(left.isNegative){
		return BigInt::lessThan_helper(right.data, left.data);
	}
	return BigInt::lessThan_helper(left.data, right.data);
}

string BigInt::addition_helper(string one, string two) {
	int carry = 0; //carry each calculation
	int sum = 0;
	int total1;
	int total2;
	string data = "";//to put the final sum in after adding the first two together
	total1 = one.size() - 1; //to stay in range
	total2 = two.size() - 1;
	while (total1 >= 0 && total2 >= 0) {
		sum = (one[total1] - '0') + (two[total2] - '0') + carry;// Calculate the sum of digits by adding the previous carry.
		data = (char)((sum % 10) + '0') + data;
		carry = sum / 10;//update carry
		total1--;
		total2--;
	}
	while (total2 >= 0) {
		sum = (two[total2] - '0') + carry;
		data = (char)((sum % 10) + '0') + data;
		carry = sum / 10;//update carry
		total2--;
	}
	while (total1 >= 0) {
		sum = (one[total1] - '0') + carry;
		data = (char)((sum % 10) + '0') + data;
		carry = sum / 10;//update carry
		total1--;
	}
	if (carry != 0) { //If after finishing adding two numbers, if there is a leftover carry, take it into the final sum.

		data = (char)(carry + '0') + data;
	}
	return data;
}

string BigInt::subtraction_helper(string one, string two) {// two-one=return
	int borrow = 0; //carry each calculation
	string data = "";//to put the final sum in after subtracting everything
	int difference = 0;
	int total1 = one.size() - 1;//to stay within the range of string
	int total2 = two.size() - 1;
	while (total1 >= 0 && total2 >= 0) {
		difference = (one[total1] - '0') - (two[total2] - '0') - borrow;//subtract '0' from each integer in the string 
		if (difference < 0) {
			borrow = 1;
			difference = difference + 10;
			data = (char)(difference + '0') + data;
		}
		else {
			borrow = 0;
			data = (char)(difference + '0') + data;
		}
		total1--;
		total2--;
	}
	while (total2 >= 0) {
		difference = (two[total2] - '0') - borrow;
		if (difference < 0) {
			difference = difference + 10;
			data = (char)(difference + '0') + data;
			borrow = 1;
			total2--;
		}
		else {
			borrow = 0;
			data = (char)(difference + '0') + data;
			total2--;
		}
	}
	while (total1 >= 0) {
		difference = (one[total1] - '0') - borrow;
		if (difference < 0) {
			difference = difference + 10;
			data = (char)(difference + '0') + data;
			borrow = 1;
			total1--;
		}
		else {
			borrow = 0;
			data = (char)(difference + '0') + data;
			total1--;
		}
	}
	int i = 0;
	while (data[i] == '0') {
		i++;
	}
	if(i > 1){
		data.erase(data.begin(), data.begin() + i);
	}
	return data;
}

BigInt operator+(const BigInt & left, const BigInt & right) {
	BigInt result {0};

	//if left is positive and right is positive give it to addition
	if (left.isNegative == right.isNegative) {
		result.data = BigInt::addition_helper(left.data, right.data);
		result.isNegative = left.isNegative;
	}
	//if left is positive and right is negative give it subtraction
	else if (BigInt::lessThan_helper(left.data, right.data)) {
		result = BigInt{ BigInt::subtraction_helper(right.data, left.data) };
		result.isNegative = right.isNegative;
		//bigger number minus smaller number
	}
	else {
		result = BigInt{ BigInt::subtraction_helper(left.data, right.data) };
		result.isNegative = left.isNegative;
	}
	return BigInt(result);
}


BigInt operator-(const BigInt & left, const BigInt & right) {
	return left + (-right);//unary operator
}


bool BigInt::lessThan_helper(string one, string two) {
	if (one.size() != two.size()) {
		return one.size() < two.size();
	}
	return one < two;
}

BigInt BigInt::operator-() const {
	BigInt result{ 0 };
	result.data = data;//assigning data to itself
	result.isNegative = !isNegative;
	return result;
}
