#include <iostream>
#include <string>
using namespace std;
#include "BigInt.h"

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
	data = to_string(x);
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
		else if (x[i] == '+') {
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
	return out << right.data;
}

bool operator<(const BigInt& left, const BigInt& right) {
	int i = 0;
	//if (left.data.length() > right.data.length()) { //comparing sizes
	//	swap(left, right);
	//}
	// comparing signs 
	if (left.isNegative == true && right.isNegative == false) {//if the left is negative and the right is positive
		return true;
	}
	else if (left.isNegative == false && right.isNegative == true) { //if the left is negative and the right is positive
		return false;
	}
	else if (left.isNegative == true && right.isNegative == true) {// if both are negative
	//comparing sizes of each 
		if (left.data.size() > right.data.size()) {
			return true;
		}
		else if (left.data.size() < right.data.size()) {
			return false;
		}
		while (left.data[i] != '\0' && right.data[i] != '\0') { //while the left and right data strings do not hit the null terminator 
			if (left.data[i] != right.data[i]) { //if they are differences spotted 
				if (left.data[i] > right.data[i]) {
					return true;
				}
				else if (left.data[i] < right.data[i]) {
					return false;
				}
				if (left.data[i] == right.data[i]) {
					return false;
				}
			}

		}
	}
	else if (!left.isNegative && !right.isNegative) {
		//check for different lengths
		if (left.data.size() < right.data.size()) {
			return true;
		}
		if (left.data.size() > right.data.size()) {
			return false;
		}
		while (left.data[i] != '\0' && right.data[i] != '\0') { //while the left and right data strings do not hit the null terminator 
			if (left.data[i] != right.data[i]) { //if they are differences spotted 
				if (left.data[i] < right.data[i]) {
					return true;
				}
				if (left.data[i] > right.data[i]) {
					return false;
				}
				else if (left.data[i] == right.data[i]) {
					return false;
				}
			}

		}
	}
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
	if (i > 1) {
		data.erase(data.begin(), data.begin() + i);
	}

	return data;
}

BigInt operator+(const BigInt& left, const BigInt& right) {
	BigInt result{ 0 };

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

BigInt operator-(const BigInt& left, const BigInt& right) {
	return left + (-right);//unary operator
}

BigInt operator*(const BigInt& left, const BigInt& right) {
	string multi_table[10];//an array of 10 strings each being the result of multiplying the first number by a digit(0-9)
	string result_string("0");//place the table within a string
	BigInt result{};//return result in this
	int i;
	result.isNegative = left.isNegative ^ right.isNegative;//xor will determine result
	//fill it from 0-9
	for (i = 0; i < 10; i++) {
		multi_table[i] = result_string;//building multiplication table
		result_string = BigInt::addition_helper(left.data, result_string);//adding table entries to each other and storing them in the string()
	}
	for (auto digit = right.data.rbegin(); digit != right.data.rend(); digit++) {//reverse begin string in reverse
		result.data = BigInt::addition_helper(multi_table[*digit - '0'], result.data);//multi_table[*digit - '0'] goes into result.data
		for (i = 0; i < 10; i++) {
			multi_table[i] = multi_table[i] + "0"; //add zero each time to a table entry/result
		}
	}
	return result;
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
	result.isNegative = !isNegative;//result will not be negative
	return result;
}

bool operator>(const BigInt& left, const BigInt& right) {
	return right < left;
}

bool operator==(const BigInt& left, const BigInt& right) {
	/*bool isNegative;
	if(left.isNegative != right.isNegative &&  left.data != right.data){
	isNegative = false;
	}
	isNegative = true;*/
	return left.isNegative == right.isNegative && left.data == right.data;
}

BigInt operator/(const BigInt& left, const BigInt& right) {
	string multi_table[10];//an array of 10 strings each being the result of multiplying the first number by a digit(0-9)
	string result_string("0");//place the table within a string
	BigInt result{};//return result in this
	result.isNegative = left.isNegative ^ right.isNegative;//xor will determine result
















}

