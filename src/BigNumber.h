#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#define MAXARRAYSIZE 10000
#define MAXNUMBERSIZE (int)1e9
#define MAXNUMBERSIZEINT 9

class Integer;
class Decimal;

class BigNumber {
public:
	long long int* integer; // 分子
	long long int* decimal; // 分母
	std::string input; // 記錄初始輸入狀態（供變數轉換使用）
	bool sign;  // + : true, - : false;

	const bool operator>(const BigNumber& post);
	const bool operator<(const BigNumber& post);
	const bool operator==(const BigNumber& post);
	const bool operator==(int ask);
};

class Integer : public BigNumber {
public:
	Integer();
	Integer(const Integer& post);
	Integer(const Decimal& post);
	Integer(const BigNumber& post);
	Integer(const std::string& post);



	const void operator=(const Integer& post);
	const Integer operator+(const Integer& post);
	const Decimal operator+(const Decimal& post);

	const Integer operator-(const Integer& post);
	const Decimal operator-(const Decimal& post);

	const Integer operator*(const Integer& post);
	const Decimal operator*(const Decimal& post);

	const Decimal operator/(const Integer& post);
	const Decimal operator/(const Decimal& post);

	friend const Integer operator-(const Integer& post);
	friend const Integer operator+(const Integer& post);

	friend const Integer factorial(const Integer& pre);

	const Integer operator^(const Integer& times);
	const Decimal operator^(const Decimal& times);

	friend std::ostream& operator<<(std::ostream& s, Integer post);
	friend std::istream& operator>>(std::istream& s, Integer& post);

	friend const bool operator>(const Integer& pre, const Integer& post);
	friend const bool operator>=(const Integer& pre, const Integer& post);
	friend const bool operator>(const Integer& pre, const Decimal& post);
	friend const bool operator>=(const Integer& pre, const Decimal& post);
	friend const bool operator<(const Integer& pre, const Integer& post);
	friend const bool operator<=(const Integer& pre, const Integer& post);
	friend const bool operator<(const Integer& pre, const Decimal& post);
	friend const bool operator<=(const Integer& pre, const Decimal& post);
	friend const bool operator==(const Integer& pre, const Integer& post);
	friend const bool operator==(const Integer& pre, const Decimal& post);
	friend const bool operator==(const Integer& pre, int ask);

	Decimal squareRoot();

};

class Decimal : public BigNumber {
public:
	Decimal();
	Decimal(const Decimal& post);
	Decimal(const BigNumber& post);
	Decimal(const std::string& post);

	//std::ostream& operator<<(std::ostream& os, const Decimal& num);

	const void operator=(const Decimal& post);
	const Decimal operator+(const Integer& post);
	const Decimal operator+(const Decimal& post);

	const Decimal operator-(const Integer& post);
	const Decimal operator-(const Decimal& post);

	const Decimal operator*(const Integer& post);
	const Decimal operator*(const Decimal& post);

	const Decimal operator/(const Integer& post);
	const Decimal operator/(const Decimal& post);

	friend const Decimal operator-(const Decimal& post);
	friend const Decimal operator+(const Decimal& post);

	friend const Decimal factorial(const Decimal& post);

	const Decimal operator^(const Integer& times);
	const Decimal operator^(const Decimal& times);

	friend std::ostream& operator<<(std::ostream& output, Decimal post);
	friend std::istream& operator>>(std::istream& input, Decimal post);

	friend const bool operator>(const Decimal& pre, const Integer& post);
	friend const bool operator>=(const Decimal& pre, const Integer& post);
	friend const bool operator>(const Decimal& pre, const Decimal& post);
	friend const bool operator>=(const Decimal& pre, const Decimal& post);
	friend const bool operator<(const Decimal& pre, const Integer& post);
	friend const bool operator<=(const Decimal& pre, const Integer& post);
	friend const bool operator<(const Decimal& pre, const Decimal& post);
	friend const bool operator<=(const Decimal& pre, const Decimal& post);
	friend const bool operator==(const Decimal& pre, const Integer& post);
	friend const bool operator==(const Decimal& pre, const Decimal& post);
	friend const bool operator==(const Decimal& pre, int ask);

	Decimal squareRoot();
};


const Integer add(const Integer& pre, const Integer& post);
const Decimal add(const Integer& pre, const Decimal& post);
const Decimal add(const Decimal& pre, const Integer& post);
const Decimal add(const Decimal& pre, const Decimal& post);

const Integer minus(const Integer& pre, const Integer& post);
const Decimal minus(const Integer& pre, const Decimal& post);
const Decimal minus(const Decimal& pre, const Integer& post);
const Decimal minus(const Decimal& pre, const Decimal& post);

const Integer multi(const long long int pre[], const long long int post[]);

int Stoi(const std::string& post);

const Integer classIntegerTrans(const long long int post[]);

const Integer gcd(const Integer& pre, const Integer& post);

const std::string itos(const long long int post[]);

const std::string minus(const std::string& pre, const std::string& post);
const std::string division1(const std::string& dividend, const std::string& divisor); // return integer
const std::string division2(const std::string& dividend, const std::string& divisor); // return decimal 
const std::string multiply(std::string s1, std::string s2);
const std::string mod(const std::string& pre, const std::string& post);
const bool operator<(const std::string& pre, const std::string& post);
const bool operator>(const std::string& pre, const std::string& post);
const bool operator>=(const std::string& pre, const std::string& post);
