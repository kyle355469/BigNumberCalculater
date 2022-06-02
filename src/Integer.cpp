#include "BigNumber.h"

Integer::Integer() {
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

Integer::Integer(const Integer& post) {
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	for (int i = 0; i < MAXARRAYSIZE; i++)
	{
		this->integer[i] = post.integer[i];
		this->decimal[i] = post.decimal[i];
	}
	this->sign = post.sign;
	this->input = post.input;
}

Integer::Integer(const Decimal& post) {
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	Integer tmp = division1(itos(post.integer), itos(post.decimal));
	*this = tmp;
	this->sign = post.sign;
}

Integer::Integer(const BigNumber& post) {
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		this->integer[i] = post.integer[i];
		this->decimal[i] = 0;
	}
	this->decimal[0] = 1;
	int pos = post.input.find(".");
	if (pos != std::string::npos) {
		this->input = post.input.substr(0, pos);
	}
	else {
		this->input = post.input;
	}
	this->sign = post.sign;
}

Integer::Integer(const std::string& post) {

	this->sign = true;
	integer = new long long int[MAXARRAYSIZE]();
	decimal = new long long int[MAXARRAYSIZE]();
	std::string tmp = post;
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i] == '.') {
			tmp = tmp.substr(0, i);
			break;
		}
		if (i == tmp.size() - 1) {
			break;
		}
	}
	this->input = tmp;
	int j = 0;
	while (tmp.size() > MAXNUMBERSIZEINT) {
		this->integer[j] = Stoi(tmp.substr(tmp.size() - MAXNUMBERSIZEINT, MAXNUMBERSIZEINT));
		tmp.erase(tmp.size() - MAXNUMBERSIZEINT, MAXNUMBERSIZEINT);
		++j;
	}
	this->integer[j] = Stoi(tmp);
	this->decimal[0] = 1;
}

const void Integer::operator=(const Integer& post) {
	// std::cout << "come inconst void Integer::operator=(const Integer& post)\n";
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

const Integer Integer::operator+(const Integer& post) {
	// std::cout << "come in const Integer Integer::operator+(const Integer& post)\n";
	if (this->sign && post.sign) {
		return add(*this, post);
	}
	else if (post.sign == true) { //-a + b = b - a
		Integer tmp = *this;
		tmp.sign = true;
		return minus(post, tmp);
	}
	else if (this->sign == true) { // a + (-b) = a - b
		Integer tmp = post;
		tmp.sign = true;
		return minus(*this, tmp);
	}
	else {  // -a + -b = -(a + b)
		Integer tmp1 = *this;
		Integer tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return -add(tmp1, tmp2);
	}
}

const Decimal Integer::operator+(const Decimal& post) {
	// std::cout << "come in const Integer Integer::operator+(const Decimal& post)\n";
	if (this->sign && post.sign) {
		return add(*this, post);
	}
	else if (post.sign == true) {
		Integer tmp = *this;
		tmp.sign = true;
		return minus(post, *this);
	}
	else if (this->sign == true) {
		Decimal tmp = post;
		tmp.sign = true;
		return minus(*this, tmp);
	}
	else {
		Integer tmp1 = *this;
		Decimal tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return -add(tmp1, tmp2);
	}
}

const Integer Integer::operator-(const Integer& post) {
	// std::cout << "come in const Integer Integer::operator-(const Integer& post)\n";
	if (this->sign && post.sign) {
		return minus(*this, post);
	}
	else if (post.sign == true) { // -a - b = -(a + b)
		Integer tmp = *this;
		tmp.sign = true;
		return -add(tmp, post);
	}
	else if (this->sign == true) { // a - (-b) = a+b
		Integer tmp = post;
		tmp.sign = true;
		return add(*this, tmp);
	}
	else { // -a - (-b) = b - a;
		Integer tmp1 = *this;
		Integer tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return minus(tmp2, tmp1);
	}
}

const Decimal Integer::operator-(const Decimal& post) {
	// std::cout << "come in const Decimal Integer::operator-(const Decimal& post)\n";
	if (this->sign && post.sign) {
		return minus(*this, post);
	}
	else if (post.sign == true) {
		Integer tmp = *this;
		tmp.sign = true;
		return -add(tmp, post);
	}
	else if (this->sign == true) {
		Decimal tmp = post;
		tmp.sign = true;
		return add(*this, tmp);
	}
	else {
		Integer tmp1 = *this;
		Decimal tmp2 = post;
		tmp1.sign = true;
		tmp2.sign = true;
		return minus(tmp2, tmp1);
	}
}

const Integer Integer::operator*(const Integer& post) {
	// std::cout << "come in const Integer Integer::operator*(const Integer& post)\n";
	if (*this == 0 || post == 0) {
		return Integer("0");
	}
	else if (*this == 1) {
		return Integer(post);
	}
	else if (post == 1 && post.sign) {
		return Integer(*this);
	}
	else if (post == 1 && !post.sign) {
		Integer tmp = *this;
		tmp.sign = !tmp.sign;
	}
	Integer tmp;
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		for (int j = 0; j < MAXARRAYSIZE; j++) {
			if (i + j >= MAXARRAYSIZE || this->integer[i] == 0 || post.integer[i] == 0) {
				continue;
			}
			else {
				tmp.integer[i + j] += this->integer[i] * post.integer[j];
			}
		}
	}
	for (int i = 0; i < MAXARRAYSIZE - 1; i++) {
		tmp.integer[i + 1] += tmp.integer[i] / MAXNUMBERSIZE;
		tmp.integer[i] = tmp.integer[i] % MAXNUMBERSIZE;
	}
	if (!this->sign && !post.sign || this->sign && post.sign) {
		tmp.sign = true;
	}
	else {
		tmp.sign = false;
	}
	return tmp;
}

const Decimal Integer::operator*(const Decimal& post) {
	// std::cout << "come in const Decimal Integer::operator*(const Decimal& post)\n";
	if (*this == 0 || post == 0) {
		return Decimal("0");
	}
	else if (*this == 1) {
		return Decimal(post);
	}
	else if (post == 1) {
		return Decimal(*this);
	}
	Decimal tmp;
	Integer first = *this;
	Integer second = classIntegerTrans(post.integer);
	Integer base = classIntegerTrans(post.decimal);
	Integer hcf = gcd(first, base);
	first = first / hcf;
	base = base / hcf;
	if (!(first == 1)) {
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

const Decimal Integer::operator/(const Integer& post) {
	// std::cout << "come in const Decimal Integer::operator/(const Integer& post)\n";
	if (post == 1) {
		return Decimal(*this);
	}
	Decimal tmp;
	Integer upper = classIntegerTrans(this->integer);
	Integer base = classIntegerTrans(post.integer);
	Integer hcf = gcd(upper, base);
	//std::cout << hcf << "\n";
	upper = division1(itos(upper.integer), itos(hcf.integer));
	base = division1(itos(base.integer), itos(hcf.integer));
	//std::cout << upper << "\n";
	//std::cout << base << "\n";
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = upper.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	//std::cout << tmp.integer[0] << "\n";
	//std::cout << tmp.decimal[0] << "\n";
	if (!this->sign && !post.sign || this->sign && post.sign) {
		tmp.sign = true;
	}
	else {
		tmp.sign = false;
	}
	return tmp;
}

const Decimal Integer::operator/(const Decimal& post) {
	// std::cout << "come in const Decimal Integer::operator/(const Decimal& post)\n";
	if (post == 1) {
		return Decimal(*this);
	}
	Decimal tmp;
	Integer upper = multi(this->integer, post.decimal);
	Integer base = classIntegerTrans(post.integer);
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

const Integer operator-(const Integer& post) {
	Integer tmp = post;
	tmp.sign = !post.sign;
	return tmp;
}

const Integer operator+(const Integer& post) {
	Integer tmp = post;
	return tmp;
}

const Integer factorial(const Integer& pre) {
	std::string s = itos(pre.integer);
	// std::cout << "S: " << s << "\n";
	std::string tmp = "1";
	int rec = 10000;
	while (s != "0") {
		tmp = multiply(tmp, s);
		s = minus(s, "1");
		// std::cout << rec-- << std::endl;
	}
	return tmp;
}

const Integer Integer::operator^(const Integer& times) {
	if (times == 0) {
		return Integer("1");
	}
	else if (times == 1) {
		return Integer(*this);
	}
	Integer tmp = times;
	Integer ans = *this;
	Integer step("1");
	while (!(tmp == 1)) {
		ans = ans * *this;
		tmp = tmp - step;
	}
	return ans;
}

const Decimal Integer::operator^(const Decimal& times) {
	if (*this == 0) {
		return Decimal("0");
	}
	else if (*this == 1) {
		return Decimal("1");
	}
	Decimal ans = *this;
	Integer tmp = times;
	Integer step("1");
	while (!(tmp == 0)) {
		ans = ans * *this;
		tmp = tmp - step;
	}
	ans = ans * this->squareRoot();
	return ans;
}

std::ostream& operator<<(std::ostream& output, Integer post) {
	if (!post.sign) {
		output << "-";
	}
	bool check = false;
	for (int i = MAXARRAYSIZE - 1; i >= 0; i--) {
		if (i == 0 && post.integer[i] == 0 && !check) {
			output << "0";
			break;
		}
		if (post.integer[i] == 0 && !check) {
			continue;
		}
		else if (post.integer[i] == 0 && check) {
			for (int i = 0; i < MAXNUMBERSIZEINT; i++) {
				output << "0";
			}
		}
		else if (post.integer[i] != 0 && !check) {
			check = true;
			std::string tmp = std::to_string(post.integer[i]);
			output << tmp;
		}
		else if (post.integer[i] != 0 && check) {
			std::string tmp = std::to_string(post.integer[i]);
			while (tmp.size() < MAXNUMBERSIZEINT) {
				tmp.insert(0, "0");
			}
			output << tmp;
		}
	}
	output << "\n";
	return output;
}

std::istream& operator>>(std::istream& input, Integer& post) {
	std::string tmp;
	input >> tmp;
	post = tmp;
	return input;
}

const bool operator>(const Integer& pre, const Integer& post) {
	for (int i = MAXARRAYSIZE - 1; i >= 0; i--) {
		if (pre.integer[i] != post.integer[i]) {
			return pre.integer[i] > post.integer[i];
		}
	}
	return false;
}

const bool operator>=(const Integer& pre, const Integer& post) {
	for (int i = MAXARRAYSIZE - 1; i >= 0; i--) {
		if (pre.integer[i] != post.integer[i]) {
			return pre.integer[i] > post.integer[i];
		}
	}
	return true;
}

const bool operator>(const Integer& pre, const Decimal& post) {
	Integer first = multi(pre.integer, post.decimal);
	Integer second = classIntegerTrans(post.integer);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] > second.integer[i];
		}
	}
	return false;
}

const bool operator>=(const Integer& pre, const Decimal& post) {
	Integer first = multi(pre.integer, post.decimal);
	Integer second = classIntegerTrans(post.integer);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] > second.integer[i];
		}
	}
	return true;
}

const bool operator<(const Integer& pre, const Integer& post) {
	for (int i = MAXARRAYSIZE - 1; i >= 0; i--) {
		if (pre.integer[i] != post.integer[i]) {
			return pre.integer[i] < post.integer[i];
		}
	}
	return false;
}

const bool operator<=(const Integer& pre, const Integer& post) {
	for (int i = MAXARRAYSIZE - 1; i >= 0; i--) {
		if (pre.integer[i] != post.integer[i]) {
			return pre.integer[i] < post.integer[i];
		}
	}
	return true;
}

const bool operator<(const Integer& pre, const Decimal& post) {
	Integer first = multi(pre.integer, post.decimal);
	Integer second = classIntegerTrans(post.integer);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return false;
}

const bool operator<=(const Integer& pre, const Decimal& post) {
	Integer first = multi(pre.integer, post.decimal);
	Integer second = classIntegerTrans(post.integer);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return true;
}

const bool operator==(const Integer& pre, const Integer& post) {
	for (int i = MAXARRAYSIZE - 1; i >= 0; i--) {
		if (pre.integer[i] != post.integer[i]) {
			return false;
		}
	}
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (pre.decimal[i] != post.decimal[i]) {
			return false;
		}
	}
	return true;
}

const bool operator==(const Integer& pre, const Decimal& post) {
	Integer first = multi(pre.integer, post.decimal);
	Integer second = classIntegerTrans(post.integer);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return false;
		}
	}
	return true;
}

const bool operator==(const Integer& pre, int ask) {
	for (int i = MAXARRAYSIZE - 1; i >= 1; i--) {
		if (pre.integer[i] != 0) {
			return false;
		}
	}
	if (pre.integer[0] == ask) {
		return true;
	}
	else {
		return false;
	}
}

Decimal Integer::squareRoot() {
	// std::cout << "*************************************\n";
	// std::cout << "come in Decimal Integer::squareRoot()\n";
	// std::cout << "*************************************\n";
	if (*this == 1) {
		return Decimal("1");
	}
	else if (*this == 0) {
		return Decimal("0");
	}
	Integer tmp = classIntegerTrans(this->integer);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] /= 2;
	}
	Integer con("2");
	Integer upper1 = add(multi(tmp.integer, tmp.integer), *this);
	Integer base1 = multi(tmp.integer, con.integer);
	Decimal tmpAns = division2(itos(upper1.integer), itos(base1.integer));
	while (1) {
		// std::cout << "******************\n";
		// std::cout << "come in while loop\n";
		// std::cout << "******************\n";
		Integer upper = add(multi(tmpAns.integer, tmpAns.integer), multi(multi(tmpAns.decimal, tmpAns.decimal).integer, this->integer));
		Integer base = multi(multi(tmpAns.integer, con.integer).integer, tmpAns.decimal);
		Decimal check = division2(itos(upper.integer), itos(base.integer));
		Integer first = multi(tmpAns.integer, check.decimal);
		Integer second = multi(tmpAns.decimal, check.integer);
		bool keep = false;
		for (int i = 0; i < 13; i++) {
			if (first.integer[i] != second.integer[i]) {
				// std::cout << tmpAns << std::endl;
				tmpAns = check;
				keep = true;
				break;
			}
		}
		if (!keep) break;
	}
	return tmpAns;
}
