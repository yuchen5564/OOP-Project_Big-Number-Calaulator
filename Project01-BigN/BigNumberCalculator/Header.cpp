// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/17

//纗ㄧ计

#include "Header.h"

int sign(string _in) {
	if (_in == "(") return 0;
	if (_in == ")") return 1;

	if (_in == "+") return 2;
	if (_in == "-") return 2;
	if (_in == "*") return 3;
	if (_in == "/") return 3;
	if (_in == "^") return 4;
	if (_in == "!") return 5;

	return 999;
}

string infix2posfix(string _infix) {
	cout << _infix << endl;
	istringstream in(_infix);
	stack<string> tmp; //既笲衡じ
	string s;
	string result = {};
	while (in >> s) {
		switch (sign(s)) {
		case 2:case 3: case 4: case 5:
			while (!tmp.empty() && sign(tmp.top()) >= sign(s)) {
				result += tmp.top();
				tmp.pop();
			}
			tmp.push(s);
			break;
		case 0:	// "("
			tmp.push(s);
			break;
		case 1:	// ")"
			cout << "." << endl;
			while (tmp.top() != "(") {
				result += tmp.top();
				tmp.pop();
			}
			tmp.pop();
			break;
		case 999:
			result += s;
			break;
		}
		result += ' ';
	}
	while (!tmp.empty()) {
		result += tmp.top();
		tmp.pop();
	}
	return result;
}

//干0
void fill0(string* s, int n) {
	int len = s->length();
	for (int i = 0; i < n - len; i++) {
		*s = '0' + *s;
	}
}

//睲埃秨繷緇0
string clear0(string s) {
	int len = s.length();
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '-') continue;
		if (s[i] != '0') break;
		else count++;
	}
	if (count == len) s = "0";
	else if (s[0] == '-') s.erase(1, count);
	else s.erase(0, count);
	return s;
}

//﹟ゼ矪瞶计场だ(yuchen @ 2022.04.17)
string add(string s1, string s2) {
	string result = {};
	bool sign = 0;
	if (s1[0] == '-' && s2[0] != '-') {
		s1.erase(0, 1);
		return sub(s2, s1);
	}
	else if (s2[0] == '-' && s1[0] != '-') {
		s2.erase(0, 1);
		return sub(s1, s2);
	}
	else if (s1[0] == '-' && s2[0] == '-') {
		sign = 1;
		s1.erase(0, 1);
		s2.erase(0, 1);
	}

	int len = 0, carry = 0, tmp = 0;
	if (s1.length() > s2.length()) {
		len = s1.length();
		fill0(&s2, len);
	}
	else {
		len = s2.length();
		fill0(&s1, len);
	}

	for (int i = len - 1; i >= 0; i--) {
		tmp = s1[i] - '0' + s2[i] - '0' + carry;
		if (tmp >= 10) {
			carry = 1;
			tmp -= 10;
		}
		else {
			carry = 0;
		}
		result = (char)(tmp + '0') + result;
	}
	if (carry == 1) {
		result = '1' + result;
	}
	if (sign) result = '-' + result;
	return result;
}

//﹟ゼ矪瞶计场だ(yuchen @ 2022.04.17)
string sub(string s1, string s2) {
	string result = {};
	bool sign = 0;
	if (s1[0] == '-' && s2[0] != '-') {
		s1.erase(0, 1);
		result = add(s1, s2);
		result = '-' + result;
		return result;
	}
	else if (s2[0] == '-' && s1[0] != '-') {
		s2.erase(0, 1);
		return add(s1, s2);
	}
	else if (s1[0] == '-' && s2[0] == '-') {
		sign = 1;
		s1.erase(0, 1);
		s2.erase(0, 1);
	}

	int len = 0, borrow = 0, tmp = 0;
	if (s1.length() > s2.length()) {
		len = s1.length();
		fill0(&s2, len);
	}
	else {
		len = s2.length();
		fill0(&s1, len);
	}

	for (int i = len - 1; i >= 0; i--) {
		tmp = (s1[i] - '0') - (s2[i] - '0') - borrow;
		if (tmp < 0) {
			borrow = 1;
			tmp += 10;
		}
		else {
			borrow = 0;
		}
		result = (char)(tmp + '0') + result;
	}
	//璽计矪瞶
	if (borrow == 1) {
		for (int i = 0; i < len; i++) {
			if ((i == len - 1) && result[i] != '0') result[i] = (char)(10 - (result[i] - '0') + '0');
			else if ((i == len - 1) && result[i] == '0') continue;
			else if ((i == len - 2) && result[len - 1] == '0') result[i] = (char)(10 - (result[i] - '0') + '0');
			else result[i] = (char)(9 - (result[i] - '0') + '0');
		}
		result = '-' + result;
	}
	if (sign && result[0] != '-') result = '-' + result;
	else if (sign && result[0] == '-') result.erase(0, 1);
	return clear0(result);
}
