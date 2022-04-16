// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/15

//class函式內容

#include "BigN.h"

// 運算子優先權
// 輸入: 數值字串或運算子字串
// 返回: 對應優先權數字，若非運算子返回0
int sign(string _in) {
	if (_in == "+") return 1;
	if (_in == "-") return 1;
	if (_in == "*") return 2;
	if (_in == "/") return 2;
	if (_in == "^") return 3;
	if (_in == "!") return 4;
	if (_in == "(") return 99;
	if (_in == ")") return 100;
	return 0;
}

// 中序式轉後序式
// 輸入: 中序式字串，每個數和符號之間要有一個空格(e.g. 1+2+3: 1 + 2 + 3)
// 返回: 後序式字串，每個數和符號之間會有一個空格(e.g. 12+3+: 1 2 + 3 +)
string infix2posfix(string _infix) {
	istringstream in(_infix);
	stack<string> tmp; //暫存運算元
	stack<string> postfix; //儲存轉換後格式
	string s;
	while (in >> s) {
		switch (sign(s)) {
		case 1:case 2: case 3: case 4:
			while (!tmp.empty() && sign(tmp.top()) >= sign(s)) {
				postfix.push(tmp.top());
				tmp.pop();
			}
			tmp.push(s);
			break;
		case 99:	// "("
			tmp.push(s);
			break;
		case 100:	// ")"
			while (tmp.top() != "(") {
				postfix.push(tmp.top());
				tmp.pop();
			}
			tmp.pop();
			break;
		default:
			postfix.push(s);
			break;
		}
	}
	while (!tmp.empty()) {
		postfix.push(tmp.top());
		tmp.pop();
	}
	string result = {};
	while (!postfix.empty()) {
		result = postfix.top() + " " + result;
		postfix.pop();
	}
	//cout << output << endl;
	return result;
}

void BigN::processInput(string _in) {
	
}
