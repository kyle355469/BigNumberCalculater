#include "BigNumber.h"

const Integer add(const Integer& pre, const Integer& post) {
	//// std::cout<< "come in const Integer add(const Integer& pre, const Integer& post)\n";
	Integer tmp = pre;
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] += post.integer[i];
		if (i != MAXARRAYSIZE - 1) {
			tmp.integer[i + 1] += tmp.integer[i] / MAXNUMBERSIZE;
			tmp.integer[i] = tmp.integer[i] % MAXNUMBERSIZE;
		}
	}
	return tmp;
}

const Decimal add(const Integer& pre, const Decimal& post) {
	//// std::cout << "come in const Decimal add(const Integer& pre, const Decimal& ""post) \n";
	Decimal tmp;
	Integer base = classIntegerTrans(post.decimal);
	Integer upper =
		add(multi(pre.integer, post.decimal), classIntegerTrans(post.integer));
	Integer hcf = gcd(base, upper);
	base = division1(itos(base.integer), itos(hcf.integer));
	upper = division1(itos(upper.integer), itos(hcf.integer));
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = upper.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	return tmp;
}

const Decimal add(const Decimal& pre, const Integer& post) {
	//// std::cout << "come in const Decimal add(const Decimal& pre, const Integer& ""post) \n";
	Decimal tmp;
	Integer base = classIntegerTrans(pre.decimal);
	Integer upper = add(multi(pre.decimal, post.integer), classIntegerTrans(pre.integer));
	Integer hcf = gcd(base, upper);
	std::cout << upper << "\n" << base << "\n";
	base = division1(itos(base.integer), itos(hcf.integer));
	upper = division1(itos(upper.integer), itos(hcf.integer));
	std::cout << upper << "\n" << base << "\n";
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = upper.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	return tmp;
}

const Decimal add(const Decimal& pre, const Decimal& post) {
	//// std::cout << "come in const Decimal add(const Decimal& pre, const Decimal& "
	"post) \n";
	Decimal tmp;
	Integer base = multi(pre.decimal, post.decimal);
	Integer upper = add(multi(pre.integer, post.decimal), multi(pre.decimal, post.integer));
	Integer hcf = gcd(base, upper);
	std::cout << upper << "\n" << base << "\n";
	base = division1(itos(base.integer), itos(hcf.integer));
	upper = division1(itos(upper.integer), itos(hcf.integer));
	std::cout << upper << "\n" << base << "\n";
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = upper.integer[i];
		tmp.decimal[i] = base.integer[i];
	}
	return tmp;
}

const Integer minus(const Integer& pre, const Integer& post) {
	// // std::cout << "come in const Integer minus(const Integer& pre, const
	// Integer& post)\n";
	if (pre == post) {
		return Integer("0");
	}
	else if (pre > post) {
		Integer tmp = pre;
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] -= post.integer[i];
		}
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			if (tmp.integer[i] < 0) {
				tmp.integer[i + 1] -= 1;
				tmp.integer[i] += MAXNUMBERSIZE;
			}
		}
		return tmp;
	}
	else {
		Integer tmp = post;
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] -= pre.integer[i];
		}
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			if (tmp.integer[i] > 0) {
				tmp.integer[i + 1] -= 1;
				tmp.integer[i] += MAXNUMBERSIZE;
			}
		}
		tmp.sign = !tmp.sign;
		return tmp;
	}
}

const Decimal minus(const Integer& pre, const Decimal& post) {
	//// std::cout << "come in const Decimal minus(const Integer& pre, const Decimal& ""post)\n";
	Decimal tmp;
	Integer base = classIntegerTrans(post.decimal);
	Integer first = multi(pre.integer, post.decimal);
	Integer second = classIntegerTrans(post.integer);
	if (first >= second) {
		Integer after = minus(first, second);
		if (after == 0) {
			return tmp;
		}
		Integer hcf = gcd(after, base);
		base = division1(itos(base.integer), itos(hcf.integer));
		after = division1(itos(after.integer), itos(hcf.integer));
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] = after.integer[i];
			tmp.decimal[i] = base.integer[i];
		}
	}
	else {
		Integer after = minus(second, first);
		Integer hcf = gcd(after, base);
		base = division1(itos(base.integer), itos(hcf.integer));
		after = division1(itos(after.integer), itos(hcf.integer));
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] = after.integer[i];
			tmp.decimal[i] = base.integer[i];
		}
		tmp.sign = !tmp.sign;
	}
	return tmp;
}

const Decimal minus(const Decimal& pre, const Integer& post) {
	//// std::cout << "come in const Decimal minus(const Decimal& pre, const Integer& ""post)\n";
	Decimal tmp;
	Integer base = classIntegerTrans(pre.decimal);
	Integer first = classIntegerTrans(pre.integer);
	Integer second = multi(post.integer, pre.decimal);
	if (first >= second) {
		Integer after = minus(first, second);
		if (after == 0) {
			return tmp;
		}
		Integer hcf = gcd(after, base);
		base = division1(itos(base.integer), itos(hcf.integer));
		after = division1(itos(after.integer), itos(hcf.integer));
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] = after.integer[i];
			tmp.decimal[i] = base.integer[i];
		}
	}
	else {
		Integer after = minus(second, first);
		Integer hcf = gcd(after, base);
		base = division1(itos(base.integer), itos(hcf.integer));
		after = division1(itos(after.integer), itos(hcf.integer));
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] = after.integer[i];
			tmp.decimal[i] = base.integer[i];
		}
		tmp.sign = !tmp.sign;
	}
	return tmp;
}

const Decimal minus(const Decimal& pre, const Decimal& post) {
	//// std::cout << "come in const Decimal minus(const Decimal& pre, const Decimal& ""post)\n";
	Decimal tmp;
	Integer base = multi(pre.decimal, post.decimal);
	Integer first = multi(pre.integer, post.decimal);
	Integer second = multi(pre.decimal, post.integer);
	if (first >= second) {
		Integer after = minus(first, second);
		if (after == 0) {
			return tmp;
		}
		Integer hcf = gcd(after, base);
		base = division1(itos(base.integer), itos(hcf.integer));
		after = division1(itos(after.integer), itos(hcf.integer));
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] = after.integer[i];
			tmp.decimal[i] = base.integer[i];
		}
	}
	else {
		Integer after = minus(second, first);
		Integer hcf = gcd(after, base);
		base = division1(itos(base.integer), itos(hcf.integer));
		after = division1(itos(after.integer), itos(hcf.integer));
		for (int i = 0; i < MAXARRAYSIZE; i++) {
			tmp.integer[i] = after.integer[i];
			tmp.decimal[i] = base.integer[i];
		}
		tmp.sign = !tmp.sign;
	}
	return tmp;
}

int Stoi(const std::string& post) {
	//// std::cout << "come in int Stoi(const std::string& post)\n";
	int sign = 1;
	int i = 0;
	int result = 0;
	if (post[0] == '-') {
		sign = -1;
		i = 1;
	}
	for (; i < post.size(); i++) {
		result *= 10;
		result += int(post[i]) - 48;
	}
	result *= sign;
	return result;
}

const bool BigNumber::operator>(const BigNumber& post) {
	//// std::cout
	//	<< "come in const bool BigNumber::operator>(const BigNumber& post)\n";
	Integer first = multi(this->integer, post.decimal);
	Integer second = multi(post.integer, this->decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] > second.integer[i];
		}
	}
	return false;
}

const bool BigNumber::operator<(const BigNumber& post) {
	//// std::cout
	//	<< "come in const bool BigNumber::operator<(const BigNumber& post)\n";
	Integer first = multi(this->integer, post.decimal);
	Integer second = multi(post.integer, this->decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return first.integer[i] < second.integer[i];
		}
	}
	return false;
}

const bool BigNumber::operator==(const BigNumber& post) {
	//// std::cout
	//	<< "come in const bool BigNumber::operator==(const BigNumber& post)\n";
	Integer first = multi(this->integer, post.decimal);
	Integer second = multi(post.integer, this->decimal);
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		if (first.integer[i] != second.integer[i]) {
			return false;
		}
	}
	return true;
}

const bool BigNumber::operator==(int ask) {
	//// std::cout << "come in const bool BigNumber::operator==(int ask)\n";
	for (int i = MAXARRAYSIZE - 1; i >= 1; i--) {
		if (this->integer[i] != 0) {
			return false;
		}
	}
	if (this->integer[0] == ask) {
		return true;
	}
	else {
		return false;
	}
}

const Integer multi(const long long int pre[], const long long int post[]) {
	//// std::cout << "come in const Integer multi(const long long int pre[], const "
	//	"long long int post[])\n";
	Integer tmp;
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		for (int j = 0; j < MAXARRAYSIZE; j++) {
			if (i + j >= MAXARRAYSIZE) {
				break;
			}
			tmp.integer[i + j] = tmp.integer[i + j] + pre[i] * post[j];
			if (tmp.integer[i + j] >= MAXNUMBERSIZE) {
				tmp.integer[i + j + 1] += tmp.integer[i + j] / MAXNUMBERSIZE;
				tmp.integer[i + j] = tmp.integer[i + j] % MAXNUMBERSIZE;
			}
		}
	}
	return tmp;
}

const Integer classIntegerTrans(const long long int post[]) {
	//// std::cout << "come in const Integer classIntegerTrans(const long long int "
	//	"post[])\n";
	Integer tmp;
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] = post[i];
	}
	return tmp;
}

const Integer gcd(const Integer& pre, const Integer& post) {
	//// std::cout
	//	<< "come in const Integer gcd(const Integer& pre, const Integer& post)\n";
	if (pre == post) {
		return post;
	}
	else if (pre == 1 || post == 1) {
		return Integer("1");
	}
	else if (pre > post) {
		Integer tmp = mod(itos(pre.integer), itos(post.integer));
		if (tmp == 0) {
			return post;
		}
		else {

			return gcd(post, tmp);
		}
	}
	else {
		Integer tmp = mod(itos(post.integer), itos(pre.integer));
		if (tmp == 0) {
			return pre;
		}
		else {
			return gcd(pre, tmp);
		}
	}
}

const std::string itos(const long long int post[]) {
	//// std::cout << "come in const std::string itos(const long long int post[])\n";
	bool check = false;
	std::string trans;
	trans.clear();
	for (int i = MAXARRAYSIZE - 1; i >= 0; i--) {
		if (post[i] == 0 && !check) {
			continue;
		}
		else if (post[i] == 0 && check) {
			for (int i = 0; i < MAXNUMBERSIZEINT; i++) {
				trans += "0";
			}
		}
		else if (post[i] != 0 && !check) {
			check = true;
			std::string tmp = std::to_string(post[i]);
			trans += tmp;
		}
		else {
			std::string tmp = std::to_string(post[i]);
			while (tmp.size() < MAXNUMBERSIZEINT) {
				tmp.insert(0, "0");
			}
			trans += tmp;
		}
	}
	return trans;
}

const std::string minus(const std::string& pre, const std::string& post) {
	std::string s1 = pre;
	std::string s2 = post;
	if (s1 == s2) {
		return "0";
	}
	int comp = 0;

	int i, j;
	for (j = s2.size() - 1, i = s1.size() - 1; j >= 0; j--, i--) {

		comp += s1[i] - s2[j];
		if (comp < 0) {

			int k = 1;
			while (s1[i - k] == '0') k++;
			s1[i - k]--;
			comp += pow(10, k);
		}
		s1[i] = (comp % 10) + '0';
		comp /= 10;
	}
	for (; i >= 0; i--) {

		comp += s1[i] - '0';
		if (comp < 0) {

			int k = 1;
			while (s1[i - k] == '0') k++;
			s1[i - k]--;
			comp += pow(10, k);
		}
		s1[i] = (comp % 10) + '0';
		comp /= 10;
	}
	while (s1.front() == '0') s1.erase(s1.begin());

	return s1;
}

const std::string division1(const std::string& dividend, const std::string& divisor) {
	std::string answer = "";
	std::string s1 = dividend;
	std::string s2 = divisor;
	std::string tmp;
	int count;

	if (dividend == divisor) {
		return "1";
	}
	else if (divisor == "1") {
		return dividend;
	}

	if (s1 < s2) {
		return "0";
	}

	int flag = s1.size() - s2.size() + 1;
	while (s1 < s2) {
		s1 += '0';
	}

	for (int i = s2.size(); i <= s1.size(); i++) {

		for (count = 9; count >= 1; count--) {

			tmp = multiply(s2, std::to_string(count));
			if ((s1.substr(0, i) >= tmp)) {

				int di = 0;
				for (int j = tmp.size() - 1, l = i - 1; j >= 0; j--, l--) {

					di += s1[l] - tmp[j];
					if (di < 0) {

						int k = 1;
						while (s1[l - k] == '0') k++;
						s1[l - k]--;
						di += pow(10, k);
					}
					s1[l] = (di % 10) + '0';
					di /= 10;
				}
				break;
			}
		}
		answer.push_back(count + '0');
	}

	if (flag > 0) answer.insert(answer.begin() + flag, '.');
	else {

		for (; flag < 0; flag++) answer.insert(answer.begin(), '0');
		answer.insert(answer.begin(), '.');
		answer.insert(answer.begin(), '0');
	}

	while (answer.back() == '0') answer.pop_back();
	if (answer.back() == '.') answer.pop_back();
	while (answer.front() == '0') answer.erase(answer.begin());
	if (answer.front() == '.') answer.insert(answer.begin(), '0');

	return answer;
}

const std::string division2(const std::string& dividend, const std::string& divisor) {
	std::string answer = "";
	if (dividend == divisor) {
		answer = "1.";
		for (int i = 0; i < 100; i++) {
			answer += "0";
		}
		return answer;
	}
	else if (divisor == "1") {
		answer = dividend;
		answer += ".";
		for (int i = 0; i < 100; i++) {
			answer += "0";
		}
		return answer;;
	}

	int count;
	int flag = 0;
	std::string pre = dividend;
	std::string post = divisor;
	std::string tmp;

	flag += pre.size() - post.size() + 1;
	while (pre.size() <= post.size()) {
		pre += '0';
		//flag++;
	}

	// process point
	if (pre.find('.') != pre.npos) {
		bool ignore = true;
		std::string t = pre.substr(pre.find('.') + 1, pre.size() - pre.find('.'));
		for (int i = 0; i < t.size(); i++) {
			if (t[i] != '0') {
				ignore = false;
			}
		}
		if (ignore) {
			pre = pre.substr(0, pre.find('.'));
		}
		else {
			//flag += (pre.size() - pre.find('.') - 1);
			pre.erase(pre.begin() + pre.find('.'));
		}
	}

	if (post.find('.') != post.npos) {
		bool ignore = true;
		std::string t = post.substr(post.find('.') + 1, post.size() - post.find('.'));
		for (int i = 0; i < t.size(); i++) {
			if (t[i] != '0') {
				ignore = false;
			}
		}
		if (ignore) {
			post = post.substr(0, post.find('.'));
		}
		else {
			flag += (post.size() - post.find('.') - 1);
			post.erase(post.begin() + post.find('.'));
		}
	}

	for (int i = 0; i < pre.size(); i++) {
		if (pre[i] == '0') {
			pre.erase(pre.begin());
			i--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < post.size(); i++) {
		if (post[i] == '0') {
			post.erase(post.begin());
			i--;
		}
		else {
			break;
		}
	}
	//std::cout << "pre: " << pre << "\n";
	//std::cout << "post: " << post << "\n";


	pre.append(100, '0');
	for (int i = post.size(); i <= pre.size(); i++) {

		for (count = 9; count >= 1; count--) {

			tmp = multiply(post, std::to_string(count));
			if (pre.substr(0, i) >= tmp) {

				int d = 0;
				for (int j = tmp.size() - 1, l = i - 1; j >= 0; j--, l--) {

					d += pre[l] - tmp[j];
					if (d < 0) {

						int k = 1;
						while (pre[l - k] == '0') {
							k++;
						}
						pre[l - k]--;
						d += pow(10, k);
					}
					pre[l] = (d % 10) + '0';
					d /= 10;
				}
				break;
			}
		}
		answer.push_back(count + '0');
	}

	if (flag > 0) {
		answer.insert(answer.begin() + flag, '.');
	}
	else {
		for (flag; flag < -1; flag++) {
			answer.insert(answer.begin(), '0');
		}
		answer.insert(answer.begin(), '.');
		answer.insert(answer.begin(), '0');
	}

	//std::cout << "answer: " << answer << "\n";
	/*
	if (flag > 0) {
		answer.insert(answer.begin() + flag, '.');
	}
	else {
		for (; flag < 0; flag++) {
			answer.insert(answer.begin(), '0');
		}
		answer.insert(answer.begin(), '.');
		answer.insert(answer.begin(), '0');
	}
	*/

	while (answer.front() == '0') {
		answer.erase(answer.begin());
	}
	if (answer.front() == '.') {
		answer.insert(answer.begin(), '0');
	}

	int index = answer.find('.');
	answer = answer.substr(0, index + 101);
	//std::cout << answer.size() << "\n";
	return answer;

}

const std::string multiply(std::string s1, std::string s2) {

	if (s1 == "0" || s2 == "0") return "0";

	std::string answer(s1.size() + s2.size(), 0);

	for (int i = s1.size() - 1; i >= 0; i--) {

		for (int j = s2.size() - 1; j >= 0; j--) {

			answer[i + j + 1] += (s1[i] - '0') * (s2[j] - '0');
			if (answer[i + j + 1] > 9) {

				answer[i + j] += answer[i + j + 1] / 10;
				answer[i + j + 1] = answer[i + j + 1] % 10;
			}
		}
	}


	while (answer.front() == 0) answer.erase(answer.begin());
	for (int i = 0; i < answer.size(); i++) {

		answer[i] += '0';
	}

	return answer;
}

const std::string mod(const std::string& pre, const std::string& post) {
	return minus(pre, multiply(post, division1(pre, post)));
}

const bool operator<(const std::string& pre, const std::string& post) {
	std::string s1 = pre;
	std::string s2 = post;
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] == '0') {
			s1.erase(s1.begin());
			i--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < s2.size(); i++) {
		if (s2[i] == '0') {
			s2.erase(s2.begin());
			i--;
		}
		else {
			break;
		}
	}
	if (s1 == s2) {
		return false;
	}
	else {
		if (s1.size() > s2.size()) {
			return false;
		}
		else if (s1.size() < s2.size()) {
			return true;
		}
		else {
			for (int i = 0; i < s2.size(); i++) {
				if (s2[i] > s1[i]) {
					return true;
				}
				else if (s2[i] < s1[i]) {
					return false;
				}
				else {
					continue;
				}
			}
		}
	}
}

const bool operator>(const std::string& pre, const std::string& post) {
	std::string s1 = pre;
	std::string s2 = post;
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] == '0') {
			s1.erase(s1.begin());
			i--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < s2.size(); i++) {
		if (s2[i] == '0') {
			s2.erase(s2.begin());
			i--;
		}
		else {
			break;
		}
	}
	if (s1 == s2) {
		return false;
	}
	else {
		if (s1.size() > s2.size()) {
			return true;
		}
		else if (s1.size() < s2.size()) {
			return false;
		}
		else {
			for (int i = 0; i < s2.size(); i++) {
				if (s2[i] > s1[i]) {
					return false;
				}
				else if (s2[i] < s1[i]) {
					return true;
				}
				else {
					continue;
				}
			}
		}
	}
}

const bool operator>=(const std::string& pre, const std::string& post) {
	std::string s1 = pre;
	std::string s2 = post;
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] == '0') {
			s1.erase(s1.begin());
			i--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < s2.size(); i++) {
		if (s2[i] == '0') {
			s2.erase(s2.begin());
			i--;
		}
		else {
			break;
		}
	}
	if (s1 == s2) {
		return true;
	}
	else {
		if (s1.size() > s2.size()) {
			return true;
		}
		else if (s1.size() < s2.size()) {
			return false;
		}
		else {
			for (int i = 0; i < s2.size(); i++) {
				if (s2[i] > s1[i]) {
					return false;
				}
				else if (s2[i] < s1[i]) {
					return true;
				}
				else {
					continue;
				}
			}
		}
	}
}
