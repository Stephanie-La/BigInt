#include <iostream>
#include <string>
using namespace std;

class BigInt {
public:
	BigInt(); //Initializes the BigInt to zero
	BigInt(int x);//Initializes the BigInt to have the same value as x
	explicit BigInt(string x);//Initializes the BigInt to have the value of the given string
	friend ostream& operator<<(ostream& out, const BigInt& right);

	friend BigInt operator+(const BigInt& left, const BigInt& right);
	friend BigInt operator-(const BigInt& left, const BigInt& right);
	friend BigInt operator*(const BigInt& left, const BigInt& right);
	friend BigInt operator/(const BigInt& left, const BigInt& right);
	friend BigInt operator%(const BigInt& left, const BigInt& right);


	friend bool operator<(const BigInt& left, const BigInt& right);
	friend bool operator>(const BigInt& left, const BigInt& right);
	friend bool operator==(const BigInt& left, const BigInt& right);
	BigInt operator-() const;//makes new bigint opposite or bigint

private:

	static std::string addition_helper(std::string one, std::string two);
	static std::string subtraction_helper(std::string one, std::string two);
	static bool lessThan_helper(std::string one, std::string two);
	static std::string division_helper(std::string one, std::string two);

	string data;
	bool isNegative;
};

