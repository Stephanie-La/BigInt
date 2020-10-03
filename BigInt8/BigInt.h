#include <iostream>
#include <string>

class BigInt {
public:
	BigInt(); //Initializes the BigInt to zero
	BigInt(int x);//Initializes the BigInt to have the same value as x
	explicit BigInt(std::string x);//Initializes the BigInt to have the value of the given string
	friend std::ostream& operator<<(std::ostream& out, const BigInt& right);


	friend BigInt operator+(const BigInt& left, const BigInt& right);
	friend BigInt operator-(const BigInt& left, const BigInt& right);

	friend bool operator<(const BigInt& left, const BigInt& right);
	BigInt operator-() const;//makes new bigint opposite or bigint
private:
	static std::string addition_helper(std::string one, std::string two);
	static std::string subtraction_helper(std::string one, std::string two);
	static bool lessThan_helper(std::string one, std::string two);//finds which string is smaller 

	std::string data;
	bool isNegative;
};


