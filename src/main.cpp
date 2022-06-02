#include "BigNumber.h"
#include <vector>
#include <map>
#define isAlpha(i) (i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z')
#define isNumber(i) (i >= '0' && i <= '9' || i == '.')
#define isSymbol(i) (i == '+' || i == '-' || i == '*' || i == '/' || i == '^') 
#define isAllSymbol(i) (i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == '(' || i == '!') 
// isAllSymbol is without ')' to cal.
#define isSign(i) (i == '+' || i == '-')

using namespace std;

//map<string, BigNumber*> variables;
vector<pair<string, BigNumber>> variables;
vector<pair<BigNumber, bool>> numbers;
// vector<char> symbol;

bool use = false;
bool isIntegerCheck(Decimal post);
int variableCheck(string name);
bool preprocess(string& input);
bool orderAdding(string& input);
bool cal(string& input);
bool variableToCal(string& input);
bool allInOneProcess(string& input);

int main() {
	string origin;
	while (getline(cin, origin)) {

		numbers.clear();
		int varPos = variableCheck(origin);
		int st = origin.find("Set");
		bool non = true;

		for (int i = 0; i < st; i++) {
			if (origin[i] != ' ') {
				non = false;
				break;
			}
		}

		if (st != string::npos && non) {

			string type, name, value;
			int i, j;
			bool once = false;

			for (i = st + 3; i < origin.size(); i++) {
				if (origin[i] != ' ' && !once) {
					once = true;
					j = i;
				}
				else if (origin[i] == ' ' && once) {
					type = origin.substr(j, i - j);
					break;
				}
			}

			once = false;
			for (i = i + 1; i < origin.size(); i++) {
				if (origin[i] != ' ' && !once) {
					once = true;
					j = i;
				}
				if (origin[i] == ' ' && once) {
					name = origin.substr(j, i - j);
					break;
				}
			}

			once = false;
			for (i = origin.find("=") + 1; i < origin.size(); i++) {
				if (origin[i] != ' ' && !once) {
					once = true;
					j = i;
				}
				else if (origin[i] == ' ' && once) {
					value = origin.substr(j, i - j);
					break;
				}
				if (i == origin.size() - 1) {
					value = origin.substr(j, i - j + 1);
				}
			}
			if (!allInOneProcess(value)) {
				continue;
			}

			if (type == "Integer") {
				Integer tmp(value);
				variables.push_back(make_pair(name, tmp));
				//variables[name] = &tmp;
			}
			else if (type == "Decimal") {
				Decimal tmp(value);
				variables.push_back(make_pair(name, tmp));
				//variables[name] = &tmp;
			}
		}

		else if (varPos != -1) {
			int equalPos = origin.find("=");

			if (variables[varPos].first.size() == origin.size()) {  // print
				if (variables[varPos].second.input.find(".") != string::npos) {
					Decimal tmp = variables[varPos].second;
					cout << division2(itos(tmp.integer), itos(tmp.decimal)) << endl;;
				}
				else {
					Integer tmp = variables[varPos].second;
					cout << tmp;
				}
			}

			else if (equalPos != string::npos) { // calculate & save
				string var = origin.substr(equalPos + 1);
				allInOneProcess(var);
				string name = variables[varPos].first;
				variables.erase(variables.begin() + varPos);
				variables.push_back(make_pair(name, numbers[0].first));
			}
			else { // variable calculate
				if (!allInOneProcess(origin)) {
					continue;
				}
				if (numbers[0].second) {
					Integer ans = numbers[0].first;
					cout << ans << endl;
				}
				else {
					Decimal ans = numbers[0].first;
					cout << division2(itos(ans.integer), itos(ans.decimal)) << endl;
				}
			}
		}
		else if (varPos == -1 && st == string::npos){
			if (!allInOneProcess(origin)) {
				continue;
			}
			if (numbers[0].second) {
				Integer ans = numbers[0].first;
				cout << ans << endl;
			}
			else {
				Decimal ans = numbers[0].first;
				cout << division2(itos(ans.integer), itos(ans.decimal)) << endl;
			}
		}
		else if (isAlpha(origin[0])) {
			cout << "error: invalid input\n";
			continue;
		}
		cout << "\n-------------------\n";
	}
}

bool isIntegerCheck(Decimal post) {
	for (int i = 1; i < MAXARRAYSIZE; i++) {
		if (post.decimal[i] != 0) {
			return false;
		}
	}
	if (post.decimal[0] == 1) {
		return true;
	}
	return false;
}

int variableCheck(string name) {
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].first == name.substr(0, variables[i].first.size())) {
			return i;
		}
	}
	return -1; // not found
}

bool preprocess(string& input) { // 正負號判斷
	//input.insert(0, "0+");
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == ' ') {
			input.erase(i, 1);
			i--;
		}
	}
	//cout << "step 1 " << input << endl;
	/*for (int i = 0; i < input.size() - 1; i++) {
		while (isSign(input[i]) && isSign(input[i + 1]) && i < input.size() - 1) {
			if (input[i] == '+' && input[i + 1] == '+') {
				input.erase(i + 1, 1);
			}
			else if (input[i] == '-' && input[i + 1] == '+') {
				input.erase(i + 1, 1);
			}
			else if (input[i] == '+' && input[i + 1] == '-') {
				input[i] = '-';
				input.erase(i + 1, 1);
			}
			else if (input[i] == '-' && input[i + 1] == '-') {
				input[i] = '+';
				input.erase(i + 1, 1);
			}
			if (i >= input.size() - 1) {
				break;
			}
		}
	}*/
	//cout << input << endl;
	return true;
}

bool orderAdding(string& input) {
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '!') {
			input.insert(i + 1, ")");
			int check = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (input[j] == ')') {
					check++;
				}
				else if (input[j] == '(') {
					check--;
				}
				if ((!isNumber(input[j]) && check <= 0)) {
					input.insert(j + 1, "(");
					i += 2;
					break;
				}
				else if (j == 0) {
					input.insert(j, "(");
					i += 2;
					break;
				}
			}
		}
	}
	//cout << "step 2 " << input << endl;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '^') {
			int check = 0;
			for (int j = i + 1; j < input.size(); j++) {
				if (input[j] == '(') {
					check++;
				}
				else if (input[j] == ')') {
					check--;
				}
				
				if (!isNumber(input[j]) && check <= 0) {
					input.insert(j, ")");
					break;
				}
				else if (j == input.size() - 1) {
					input.insert(j + 1, ")");
					break;
				}
			}
			check = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (input[j] == ')') {
					check++;
				}
				else if (input[j] == '(') {
					check--;
				}
				
				if ((!isNumber(input[j]) && check <= 0)) {
					input.insert(j + 1, "(");
					i += 2;
					break;
				}
				else if (j == 0) {
					input.insert(j, "(");
					i += 2;
					break;
				}
			}
		}
	}
	//cout << "step 3 " << input << endl;
	for (int i = 0; i < input.size(); i++) {
		if ((input[i] == '+' || input[i] == '-') && (i == 0 || isAllSymbol(input[i - 1]))) {
			if (input[i] == '-') {
				input[i] = 'M'; // minus, to eazily recognize sign and symbol
			}
			if (input[i] == '+') {
				input.erase(i, 1);
				i--;
			}
			else {
				input.insert(i, "(");
				int check = 0;
				for (int j = i + 2; j < input.size(); j++) {
					if (input[j] == '(') {
						check++;
					}
					else if (input[j] == ')') {
						check--;
					}
					
					if (!isNumber(input[j]) && check == 0) {
						input.insert(j, ")");
						i += 2;
						break;
					}
					else if (j == input.size() - 1) {
						input.insert(j + 1, ")");
						i += 2;
						break;
					}
				}
			}

		}
	}
	//cout << "step 4 " << input << endl;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '*' || input[i] == '/') {
			int check = 0;
			for (int j = i + 1; j < input.size(); j++) {
				if (input[j] == '(') {
					check++;
				}
				else if (input[j] == ')') {
					check--;
				}
				
				if (!isNumber(input[j]) && check <= 0) {
					input.insert(j, ")");
					break;
				}
				else if (j == input.size() - 1) {
					input.insert(j + 1, ")");
					break;
				}
			}
			check = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (input[j] == ')') {
					check++;
				}
				else if (input[j] == '(') {
					check--;
				}
				
				if ((!isNumber(input[j]) && check <= 0)) {
					input.insert(j + 1, "(");
					i += 2;
					break;
				}
				else if (j == 0) {
					input.insert(j, "(");
					i += 2;
					break;
				}
			}
		}
	}
	//cout << "step 5 " << input << endl;
	for (int i = 0; i < input.size(); i++) {
		if ((input[i] == '+' || input[i] == '-') && (i != 0 && !isAllSymbol(input[i - 1]))) {
			int check = 0;
			for (int j = i + 1; j < input.size(); j++) {
				if (input[j] == '(') {
					check++;
				}
				else if (input[j] == ')') {
					check--;
				}
				
				if (!isNumber(input[j]) && check <= 0) {
					input.insert(j, ")");
					break;
				}
				else if (j == input.size() - 1) {
					input.insert(j + 1, ")");
					break;
				}
			}
			check = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (input[j] == ')') {
					check++;
				}
				else if (input[j] == '(') {
					check--;
				}
				
				if ((!isNumber(input[j]) && check <= 0) || j == 0) {
					input.insert(j, "(");
					i += 2;
					break;
				}
			}
		}
	}
	//cout << "step 6 " << input << endl;
	return true;
}

bool postfix(string& input) {
	vector<string> num;
	vector<char> sign;
	string postfixString;
	postfixString.erase(0);
	for (int i = 0; i < input.size(); i++) {
		if (isAllSymbol(input[i]) || input[i] == 'M') {
			sign.push_back(input[i]);
		}
		else if (input[i] == ')') {
			while (true) { // if '(' -> break;
				if (sign.empty()) break;

				if (sign.back() == '(') {
					sign.pop_back();
					break;
				}
				else if (sign.back() == '!' || sign.back() == 'M') {
					string tmp;
					string back = num.back();
					num.pop_back();
					tmp = back + " " + sign.back();
					sign.pop_back();
					num.push_back(tmp);
				}
				else if (isSymbol(sign.back())) {
					string tmp;
					string back = num.back();
					num.pop_back();
					string front = num.back();
					num.pop_back();
					tmp = front + " " + back + " " + sign.back();
					sign.pop_back();
					num.push_back(tmp);
				}
			}
		}
		else if (isNumber(input[i])) {
			int j;
			for (j = i; j < input.size(); j++) {
				if (!isNumber(input[j])) {
					string tmp = input.substr(i, j - i);
					num.push_back(tmp);
					i = j - 1;
					break;
				}
				else if (j == input.size() - 1) {
					string tmp = input.substr(i, j - i + 1);
					num.push_back(tmp);
					i = j;
					break;
				}
			}
		}
		/*else if(input[i] == 'M'){
			int j;
			for(j = i + 1; j < input.size(); j++){
				if(!isNumber(input[j]) || j == input.size() - 1){
					string tmp = input.substr(i, j - i);
					num.push_back(tmp);
					break;
				}
			}
			i = j - 1;
		}*/
	}
	if (!sign.empty()) {
		return false;
	}
	if (!num.empty()) {
		//cout << "number: " << num.back() << endl;
		input = num.back();
		//cout << input << endl;
	}
	//*/
	return true;
}

bool cal(string& input) {
	vector<string> post;
	int j = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == ' ') {
			string tmp = input.substr(j, i - j);
			//cout << tmp << endl;
			j = i + 1;
			post.push_back(tmp);
		}
		else if (i == input.size() - 1) {
			string tmp = input.substr(j, i - j + 1);
			//cout << tmp << endl;
			j = i + 1;
			post.push_back(tmp);
		}
	}
	for (int i = 0; i < post.size(); i++) {
		if (isNumber(post[i][0])) {
			string tmp = post[i];
			bool intOrDec = true;
			for (j = 0; j < tmp.size(); j++) {
				if (tmp[j] == '.') {
					intOrDec = false;
					break;
				}
			}
			if (intOrDec) {
				Integer num(tmp);
				numbers.push_back(make_pair(num, intOrDec));
			}
			else {
				Decimal num(tmp);
				numbers.push_back(make_pair(num, intOrDec));
			}

		}
		if (post[i] == "M") {
			//cout << "cal M ";
			pair<BigNumber, bool> tmp = numbers.back();
			tmp.first.sign = !tmp.first.sign;
			numbers.pop_back();
			if (tmp.second) {
				Integer pre = tmp.first;
				//cout << pre << "\n";
				numbers.push_back(make_pair(pre, tmp.second));
			}
			else {
				Decimal pre = tmp.first;
				//cout << pre << "\n";
				numbers.push_back(make_pair(pre, tmp.second));
			}
		}
		else if (post[i] == "!") {
			//cout << "cal ! ";
			pair<BigNumber, bool> tmp = numbers.back();
			numbers.pop_back();
			if (tmp.second) {
				Integer pre = tmp.first;
				//cout << pre << "\n";
				pre = factorial(pre);
				numbers.push_back(make_pair(pre, tmp.second));
			}
			else {
				cout << "error: 階乘須為整數\n";
				Integer pre = tmp.first;
				//cout << pre << endl;
				pre = factorial(pre);
				numbers.push_back(make_pair(pre, tmp.second));
			}
		}
		else if (post[i] == "+") {
			//cout << "cal + ";
			pair<BigNumber, bool> tmp1 = numbers.back();
			numbers.pop_back();
			pair<BigNumber, bool> tmp2 = numbers.back();
			numbers.pop_back();
			if (tmp1.second) {
				if (tmp2.second) {
					Integer pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					Integer res = pre + post;
					//cout << res << endl;
					numbers.push_back(make_pair(res, tmp1.second));
				}
				else {
					Integer pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre + post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, tmp1.second));
					}
					else {
						numbers.push_back(make_pair(res, tmp2.second));
					}
				}
			}
			else {
				if (tmp2.second) {
					Decimal pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre + post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, tmp2.second));
					}
					else {
						numbers.push_back(make_pair(res, tmp1.second));
					}
				}
				else {
					Decimal pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre + post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
			}
		}
		else if (post[i] == "-") {
			//cout << "cal -\n";
			pair<BigNumber, bool> tmp2 = numbers.back();
			numbers.pop_back();
			pair<BigNumber, bool> tmp1 = numbers.back();
			numbers.pop_back();
			if (tmp1.second) {
				if (tmp2.second) {
					Integer pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					Integer res = pre - post;
					//cout << res << endl;
					numbers.push_back(make_pair(res, tmp1.second));
				}
				else {
					Integer pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre - post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
			}
			else {
				if (tmp2.second) {
					Decimal pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre - post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
				else {
					Decimal pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre - post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
			}
		}
		else if (post[i] == "*") {
		//cout << "cal * ";
			pair<BigNumber, bool> tmp2 = numbers.back();
			numbers.pop_back();
			pair<BigNumber, bool> tmp1 = numbers.back();
			numbers.pop_back();
			if (tmp1.second) {
				if (tmp2.second) {
					Integer pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					Integer res = pre * post;
					//cout << res << endl;
					numbers.push_back(make_pair(res, tmp1.second));
				}
				else {
					Integer pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre * post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
			}
			else {
				if (tmp2.second) {
					Decimal pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre * post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
				else {
					Decimal pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre * post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
			}
		}
		else if (post[i] == "/") {
		//cout << "cal /\n";
			pair<BigNumber, bool> tmp2 = numbers.back();
			numbers.pop_back();
			pair<BigNumber, bool> tmp1 = numbers.back();
			numbers.pop_back();
			if (tmp2.first == 0) {
				cout << "error: 分母不可為零\n";
				return false;
			}
			if (tmp1.second) {
				if (tmp2.second) {
					Integer pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					if (!use) {
						Decimal res = pre / post;
						use = !use;
						if (isIntegerCheck(res)) {
							Integer newRes = res;
							numbers.push_back(make_pair(newRes, true));
						}
						else {
							numbers.push_back(make_pair(res, false));
						}
					}
					else {
						Integer res = pre / post;
						use = !use;
						if (isIntegerCheck(res)) {
							Integer newRes = res;
							numbers.push_back(make_pair(newRes, true));
						}
						else {
							numbers.push_back(make_pair(res, false));
						}
					}
					//cout << res << endl;
					
				}
				else {
					Integer pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre / post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
			}
			else {
				if (tmp2.second) {
					Decimal pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre / post;
					//cout << res << endl;
					numbers.push_back(make_pair(res, tmp1.second));
				}
				else {
					Decimal pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << " " << post << endl;
					Decimal res = pre / post;
					//cout << res << endl;
					if (isIntegerCheck(res)) {
						Integer newRes = res;
						numbers.push_back(make_pair(newRes, true));
					}
					else {
						numbers.push_back(make_pair(res, false));
					}
				}
			}
		}
		else if (post[i] == "^") {
		//cout << "cal ^\n";
			//cout << "come to ^ ******************************************************************************************************************************\n";
			pair<BigNumber, bool> tmp2 = numbers.back();
			numbers.pop_back();
			pair<BigNumber, bool> tmp1 = numbers.back();
			numbers.pop_back();
			if (tmp1.second) {
				if (tmp2.second) {
					Integer pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << "\n" << post << "\n";
					Integer res = pre ^ post;
					numbers.push_back(make_pair(res, tmp1.second));
				}
				else {
					Integer pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << "\n" << post << "\n";
					bool legal = true;
					for (int i = 1; i < MAXARRAYSIZE; i++) {
						if (post.decimal[i] != 0) {
							legal = false;
							break;
						}
					}
					if (post.decimal[0] != 2) {
						legal = false;
					}
					if (legal) {
						Decimal res = pre ^ post;
						numbers.push_back(make_pair(res, tmp2.second));
					}
					else {
						cout << "error: 冪次必須是 0.5 的倍數\n";
						return false;
					}

				}
			}
			else {
				if (tmp2.second) {
					Decimal pre = tmp1.first;
					Integer post = tmp2.first;
					//cout << pre << "\n" << post << "\n";
					Decimal res = pre ^ post;
					numbers.push_back(make_pair(res, tmp1.second));
				}
				else {
					Decimal pre = tmp1.first;
					Decimal post = tmp2.first;
					//cout << pre << "\n" << post << "\n";
					bool legal = true;
					for (int i = 1; i < MAXARRAYSIZE; i++) {
						if (post.decimal[i] != 0) {
							legal = false;
							break;
						}
					}
					if (post.decimal[0] != 2) {
						legal = false;
					}
					if (legal) {
						Decimal res = pre ^ post;
						numbers.push_back(make_pair(res, tmp2.second));
					}
					else {
						cout << "error: 冪次必須是 0.5 的倍數\n";
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool variableToCal(string& input) {
	for (int i = 0; i < input.size(); i++) {
		if (isAlpha(input[i])) {
			for (int j = i; j < input.size(); j++) {
				if (!isAlpha(input[j])) {
					int pos = variableCheck(input.substr(i, j - i));
					if (pos == -1) {
						cout << "error: variable not exist.\n";
					}
					else {
						input.erase(i, j - i);
						input.insert(i, variables[pos].second.input);
						//i = i + variables[pos].second.input.size() - 1;
					}
				}
				else if (j == input.size() - 1) {
					int pos = variableCheck(input.substr(i, j - i + 1));
					if (pos == -1) {
						cout << "error: variable not exist.\n";
					}
					else {
						input.erase(i, j - i + 1);
						input.insert(i, variables[pos].second.input);
						//i = i + variables[pos].second.input.size() - 1;
					}
				}
			}
		}
	}
	return true;
}

bool allInOneProcess(string& input) {
	bool check = true;
	check = variableToCal(input);
	if (!check) {
		return false;
	}
	for (int i = 0; i < input.size(); i++) {
		if (isAlpha(input[i])) {
			return false;
		}
	}
	check = preprocess(input);
	if(!check){
		return false;
	}
	check = orderAdding(input);
	if(!check){
		return false;
	}
	check = postfix(input);
	if(!check){
		return false;
	}
	check = cal(input);
	if(!check){
		return false;
	}
}
