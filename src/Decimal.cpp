#include "BigNumber.h"
Decimal::Decimal() {
	// std::cout << "come in Decimal::Decimal()\n";
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		this->integer[i] = 0;
		this->decimal[i] = 0;
	}
	this->decimal[0] = 1;
	this->input = "0";
	this->sign = true;
}

Decimal::Decimal(const Decimal& post) {
	// std::cout << "come in Decimal::Decimal(const Decimal& post)\n";
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	for (int i = 0; i < MAXARRAYSIZE; i++)
	{
		this->integer[i] = post.integer[i];
		this->decimal[i] = post.decimal[i];
	}
	this->input = post.input;
	this->sign = post.sign;
}

Decimal::Decimal(const BigNumber& post) {
	// std::cout << "come in Decimal::Decimal(const BigNumber& post)\n";
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		this->integer[i] = post.integer[i];
		this->decimal[i] = post.decimal[i];
	}
	this->sign = post.sign;
	this->input = post.input;
}

Decimal::Decimal(const std::string& post) {
	// std::cout << "come in Decimal::Decimal(const std::string& post)\n";
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	std::string tmp = post;
	Integer first;
	Integer second;
	this->sign = true;
	int pos = tmp.find('.');
	if (pos == std::string::npos) {
		first = tmp.substr(0, pos);
		second = Integer("1");
	}
	else {
		tmp.erase(pos, 1);
		first = tmp;
		std::string base = "1";
		base.append(tmp.size() - pos, '0');
		second = base;
	}
	Integer hcf = gcd(first, second);
	first = division1(itos(first.integer), itos(hcf.integer));
	second = division1(itos(second.integer), itos(hcf.integer));
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		this->integer[i] = first.integer[i];
		this->decimal[i] = second.integer[i];
	}
	this->input = post;
}

const void Decimal::operator=(const Decimal& post) {
	// std::cout << "come in const void Decimal::operator=(const Decimal& post)\n";
	delete[] integer;
	delete[] decimal;
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		integer[i] = post.integer[i];
		decimal[i] = post.decimal[i];
	}
	this->sign = post.sign;
	this->input = post.input;
}

const Decimal Decimal::operator+(const Integer& post) {
	// std::cout << "come in const Decimal Decimal::operator+(const Integer& post)\n";
	if (this->sign && post.sign) {
		return add(*this, post);
	}
	else if (post.sign == true) { //-a + b = b - a
		Decimal tmp = *this;
		tmp.sign = true;
		return minus(post, tmp);
	}
	else if (this->sign == true) { // a + (-b) = a - b
		Integer tmp = post;
		tmp.sign = true;
		return minus(*this, tmp);
	}
	else {  // -a + -b = -(a + b)
		Decimal tmp1 = *this;
		Integer tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return -add(tmp1, tmp2);
	}
}

const Decimal Decimal::operator+(const Decimal& post) {
	// std::cout << "come in const Decimal Decimal::operator+(const Decimal& post)\n";
	if (this->sign && post.sign) {
		return add(*this, post);
	}
	else if (post.sign == true) {
		Decimal tmp = *this;
		tmp.sign = true;
		return minus(post, *this);
	}
	else if (this->sign == true) {
		Decimal tmp = post;
		tmp.sign = true;
		return minus(*this, tmp);
	}
	else {
		Decimal tmp1 = *this;
		Decimal tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return -add(tmp1, tmp2);
	}
}

const Decimal Decimal::operator-(const Integer& post) {
	// std::cout << "come in const Decimal Decimal::operator-(const Integer& post)\n";
	if (this->sign && post.sign) {
		return minus(*this, post);
	}
	else if (post.sign == true) { // -a - b = -(a + b)
		Decimal tmp = *this;
		tmp.sign = true;
		return -add(tmp, post);
	}
	else if (this->sign == true) { // a - (-b) = a+b
		Integer tmp = post;
		tmp.sign = true;
		return add(*this, tmp);
	}
	else { // -a - (-b) = b - a;
		Decimal tmp1 = *this;
		Integer tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return minus(tmp2, tmp1);
	}
}

const Decimal Decimal::operator-(const Decimal& post) {
	// std::cout << "come in const Decimal Decimal::operator-(const Decimal& post)\n";
	if (this->sign && post.sign) {
		return minus(*this, post);
	}
	else if (post.sign == true) {
		Decimal tmp = *this;
		tmp.sign = true;
		return -add(tmp, post);
	}
	else if (this->sign == true) {
		Decimal tmp = post;
		tmp.sign = true;
		return add(*this, tmp);
	}
	else {
		Decimal tmp1 = *this;
		Decimal tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return minus(tmp2, tmp1);
	}
}

const Decimal Decimal::operator*(const Integer& post) {
	// std::cout << "come in const Decimal Decimal::operator*(const Integer& post)\n";
	if (*this == 0 && post == 0) {
		return Decimal("0");
	}
	else if (*this == 1) {
		return Decimal(post);
	}
	else if (post == 1) {
		return Decimal(*this);
	}
	Decimal tmp;
	Integer first = classIntegerTrans(this->integer);
	Integer second = post;
	Integer base = classIntegerTrans(this->decimal);
	Integer hcf = gcd(second, base);
	base = division1(itos(base.integer), itos(hcf.integer));
	second = division1(itos(second.integer), itos(hcf.integer));
	if (!(second == 1)) {
		second = second * first;
	}
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = second.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	if (!this->sign && !post.sign || this->sign && post.sign) {
		tmp.sign = true;
	}
	else {
		tmp.sign = false;
	}
	return tmp;
}

const Decimal Decimal::operator*(const Decimal& post) {
	// std::cout << "come in const Decimal Decimal::operator*(const Decimal& post)\n";
	if (*this == 0 && post == 0) {
		return Decimal("0");
	}
	else if (*this == 1) {
		return Decimal(post);
	}
	else if (post == 1) {
		return Decimal(*this);
	}
	Decimal tmp;
	Integer upper = multi(this->integer, post.integer);
	Integer base = multi(this->decimal, post.decimal);
	Integer hcf = gcd(upper, base);
	upper = division1(itos(upper.integer), itos(hcf.integer));
	base = division1(itos(base.integer), itos(hcf.integer));
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = upper.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	if (!this->sign && !post.sign || this->sign && post.sign) {
		tmp.sign = true;
	}
	else {
		tmp.sign = false;
	}
	return tmp;
}

const Decimal Decimal::operator/(const Integer& post) {
	// std::cout << "come in const Decimal Decimal::operator/(const Integer& post)\n";
	Decimal tmp;
	Integer base = multi(this->decimal, post.integer);
	Integer upper = classIntegerTrans(this->integer);
	Integer hcf = gcd(upper, base);
	upper = division1(itos(upper.integer), itos(hcf.integer));
	base = division1(itos(base.integer), itos(hcf.integer));
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = upper.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	if (!this->sign && !post.sign || this->sign && post.sign) {
		tmp.sign = true;
	}
	else {
		tmp.sign = false;
	}
	return tmp;
}

const Decimal Decimal::operator/(const Decimal& post) {
	// std::cout << "come in const Decimal Decimal::operator/(const Decimal& post)\n";
	Decimal tmp;
	Integer base = multi(this->decimal, post.integer);
	Integer upper = multi(this->integer, post.decimal);
	Integer hcf = gcd(upper, base);
	upper = division1(itos(upper.integer), itos(hcf.integer));
	base = division1(itos(base.integer), itos(hcf.integer));
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = upper.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	if (!this->sign && !post.sign || this->sign && post.sign) {
		tmp.sign = true;
	}
	else {
		tmp.sign = false;
	}
	return tmp;
}

const Decimal operator-(const Decimal& post) {
	// std::cout << "come in const Decimal operator-(const Decimal& post)\n";
	Decimal tmp = post;
	tmp.sign = !tmp.sign;
	return tmp;
}

const Decimal operator+(const Decimal& post) {
	// std::cout << "come in const Decimal operator+(const Decimal& post)\n";
	Decimal tmp = post;
	return tmp;
}

const Decimal Decimal::operator^(const Integer& times) {
	// std::cout << "come in const Decimal Decimal::operator^(const Integer& times)\n";
	if (*this == 0) {
		return Decimal("0");
	}
	else if (*this == 1) {
		return Decimal("1");
	}
	Integer tmp = times;
	Decimal ans = *this;
	Integer step("1");
	while (!(tmp == 0)) {
		ans.operator*(*this);
		tmp.operator-(step);
	}
	return ans;
}

const Decimal Decimal::operator^(const Decimal& times) {
	// std::cout << "come in const Decimal Decimal::operator^(const Decimal& times)\n";
	if (*this == 0) {
		return Decimal("0");
	}
	else if (*this == 1) {
		return Decimal("1");
	}
	Integer tmp = times;
	Decimal ans = *this;
	Integer step("1");
	while (!(tmp == 0)) {
		ans.operator*(*this);
		tmp.operator-(step);
	}
	return ans * this->squareRoot();
}

std::ostream& operator<<(std::ostream& output, Decimal post) {
	if (!post.sign) {
		output << "-";
	}
	// std::cout << "come in std::ostream& operator<<(std::ostream& output, Decimal post)\n";
	output << division2(itos(post.integer), itos(post.decimal));
	return output;
}

std::istream& operator>>(std::istream& input, Decimal post) {
	// std::cout << "come in std::istream& operator>>(std::istream& input, Decimal post) \n";
	std::string tmp;
	input >> tmp;
	int pos = tmp.find(".");
	tmp.erase(pos, 1);
	std::string first = tmp.substr(0, tmp.size());
	std::string sec = "1";
	sec.append(tmp.size() - pos, '0');
	Integer upper = first;
	Integer base = sec;
	Integer hcf = gcd(upper, base);
	upper = division1(itos(upper.integer), itos(hcf.integer));
	base = division1(itos(base.integer), itos(hcf.integer));
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		post.integer[i] = upper.integer[i];
		post.decimal[i] = base.integer[i];
	}
	return input;
}

const bool operator>(const Decimal& pre, const Integer& post) {
	// std::cout << "come in const bool operator>(const Decimal& pre, const Integer& post)\n";
	Integer first = classIntegerTrans(pre.integer);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] > second.integer[i];
		}
	}
	return false;
}

const bool operator>=(const Decimal& pre, const Integer& post) {
	// std::cout << "come in const bool operator>=(const Decimal& pre, const Integer& post)\n";
	Integer first = classIntegerTrans(pre.integer);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] > second.integer[i];
		}
	}
	return true;
}

const bool operator>(const Decimal& pre, const Decimal& post) {
	// std::cout << "come in const bool operator>(const Decimal& pre, const Decimal& post)\n";
	Integer first = multi(pre.integer, post.decimal);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] > second.integer[i];
		}
	}
	return false;
}

const bool operator>=(const Decimal& pre, const Decimal& post) {
	// std::cout << "come in const bool operator>=(const Decimal& pre, const Decimal& post)\n";
	Integer first = multi(pre.integer, post.decimal);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] > second.integer[i];
		}
	}
	return true;
}

const bool operator<(const Decimal& pre, const Integer& post) {
	// std::cout << "come in const bool operator<(const Decimal& pre, const Integer& post)\n";
	Integer first = classIntegerTrans(pre.integer);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return false;
}

const bool operator<=(const Decimal& pre, const Integer& post) {
	// std::cout << "come in const bool operator<=(const Decimal& pre, const Integer& post)\n";
	Integer first = classIntegerTrans(pre.integer);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return true;
}

const bool operator<(const Decimal& pre, const Decimal& post) {
	// std::cout << "come in const bool operator<(const Decimal& pre, const Decimal& post)\n";
	Integer first = multi(pre.integer, post.decimal);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return false;
}

const bool operator<=(const Decimal& pre, const Decimal& post) {
	// std::cout << "come in const bool operator<=(const Decimal& pre, const Decimal& post)\n";
	Integer first = multi(pre.integer, post.decimal);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return true;
}

const bool operator==(const Decimal& pre, const Integer& post) {
	// std::cout << "come in const bool operator==(const Decimal& pre, const Integer& post)\n";
	Integer first = classIntegerTrans(pre.integer);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return false;
		}
	}
	return true;
}

const bool operator==(const Decimal& pre, const Decimal& post) {
	// std::cout << "come in const bool operator==(const Decimal& pre, const Decimal& post)\n";
	Integer first = multi(pre.integer, post.decimal);
	Integer second = multi(post.integer, pre.decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return true;
}

const bool operator==(const Decimal& pre, int post) {
	// std::cout << "come in const bool operator==(const Decimal& pre, int post)\n";
	for (int i = MAXARRAYSIZE - 1; i >= 1; i--) {
		if (pre.integer[i] != 0) {
			return false;
		}
	}
	for (int i = MAXARRAYSIZE - 1; i >= 1; i--) {
		if (pre.decimal[i] != 0) {
			return false;
		}
	}
	if (pre.decimal[0] != 1) {
		return false;
	}
	if (pre.integer[0] == post) {
		return true;
	}
	return false;
}

Decimal Decimal::squareRoot() {
	// std::cout << "come in Decimal Decimal::squareRoot()\n";
	if (*this == 1) {
		return Decimal("1");
	}
	else if (*this == 0) {
		return Decimal("0");
	}
	Decimal tmp = *this;
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] /= 2;
	}
	Integer con("2");
	while (1) {
		Integer pos1 = multi(multi(tmp.integer, tmp.integer).integer, this->decimal);
		Integer pos2 = multi(multi(tmp.decimal, tmp.decimal).integer, this->integer);
		Integer upper = add(pos1, pos2);
		Integer base = multi(multi(multi(tmp.integer, con.integer).integer, tmp.decimal).integer, this->decimal);
		Decimal check = division1(itos(upper.integer), itos(base.integer));
		Integer first = multi(tmp.integer, check.decimal);
		Integer second = multi(tmp.decimal, check.integer);
		bool keep = false;
		for (int i = 0; i < 13; i++) {
			if (first.integer[i] != second.integer[i]) {
				tmp = check;
				keep = true;
				break;
			}
		}
		if (!keep) break;
	}
	return tmp;
}
