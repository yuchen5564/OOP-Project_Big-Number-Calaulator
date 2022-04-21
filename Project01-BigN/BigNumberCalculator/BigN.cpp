// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

//class函式內容

/*   2022.04.21 TO-DO   */
// 10-19+32 --> 輸入防呆

#include "BigN.h"

string BigN::countValue(string _in) {
	bool errorCode = 0;
	//算式不合法
	if (_in[0] == '*' || _in[0] == '/' || _in[0] == '^' || _in[0] == '!') {
		errorCode = 1;
		cout << "[Error] Please confirm the formula!\n";
	}

	string postfix = infix2posfix(_in);
	istringstream in(postfix);
	stack<string> tmp;
	string s, result, s1, s2;

	while (!errorCode && in >> s) {

		switch (sign(s)) {
		case 2:case 3:case 4:
			s2 = tmp.top();
			tmp.pop();
			s1 = tmp.top();
			tmp.pop();
			if (s == "+") {
				tmp.push(add(s1, s2));	//2022.04.17
			}
			else if (s == "-") {
				tmp.push(sub(s1, s2));	//2022.04.17
			}
			else if (s == "*") {
				tmp.push(multi(s1, s2)); //2022.04.18
			}
			else if (s == "/") {
				if (s2 == "0" || s2 == "0.0") { //2022.04.21 [新增] Error Code
					errorCode = 1;
					cout << "[Error] Divisor cannot be zero!\n";
				}
				else {
					tmp.push(divide(s1, s2)); //2022.04.22 By ming.
				}
			}
			else if (s == "^") {
				
			}
			break;
		case 5: //2022.04.20 [新增] Error Code: 階乘內有小數點、數字是負數
			s1 = tmp.top();
			tmp.pop();
			if (s1.find(".") != string::npos) { //2.0 ? allow
				cout << "[Error] Factorial cannot have decimals!\n";
				errorCode = 1;
			}
			else if (s1[0] == '-') {
				cout << "[Error] Factorial cannot be negative!\n";
				errorCode = 1;
			}
			else {
				tmp.push(fac(s1));
			}
			break;
		default:
			if (s[0] == '+') s.erase(0, 1);
			int len = s.length();
			bool flag = 1;
			for (int i = 0; i < len; i++) {
				if (s[0] == '-') break;
				if (s.find(".") != string::npos) break;
				if (!isdigit(s[i])) {
					flag = 0;
					break;
				}
			}
			if(flag) tmp.push(s);
			else {
				vector<Variable>::iterator i;
				flag = 0;
				for (i = list.begin(); i != list.end(); i++) {
					if (s == i->name) {
						s = i->value;
						//cout <<s<<" "<< i->value << endl;
						flag = 1;
						break;
					}
				}
				if (flag) tmp.push(s);
				else {
					cout << "[Error] \"" << s << "\" variable not found!\n";
					errorCode = 1;
				}
			}
			break;
		}
	}
	if (!errorCode) return tmp.top();
	else return "Error";
}


void BigN::setVariale(string _in) {
	//接收資料
	stringstream in(_in);
	string tmp;
	Variable var;
	string value = {};
	in >> tmp;

	if (tmp == "Set") { //輸入: Set Integer/Decimal A = 10
		in >> tmp;
		var.dataType = tmp;
		in >> tmp;
		var.name = tmp;
		in >> tmp;
		while (in >> tmp) {
			value += (' ' + tmp);
		}

		if (var.dataType == "Integer" || var.dataType == "Decimal") {
			var.value = countValue(value);
			if (var.value != "Error") {
				//去除不合型態的部分
				if (var.dataType == "Integer" && var.value.find(".") != string::npos) {
					int pos = var.value.find(".");
					var.value.erase(pos);
				}

				//尋找是否已存在
				bool find = 0;
				vector<Variable>::iterator i;
				for (i = list.begin(); i != list.end(); i++) {
					if (var.name == i->name) {
						i->dataType = var.dataType;
						i->value = var.value;
						find = 1;
					}
				}
				if (!find) list.push_back(var);
			}
		}
		else {
			cout << "[Error] Data type not found!\n";
		}
	}
	else { //輸入: A = 10 + 5 || A = A + A
		bool find = 0;
		vector<Variable>::iterator i;
		for (i = list.begin(); i != list.end(); i++) {
			if (tmp == i->name) {
				find = 1;
				in >> tmp;
				while (in >> tmp) {
					value += (' ' + tmp);
				}
				value = countValue(value);
				if (var.value != "Error") {
					if (i->dataType == "Integer" && value.find(".") != string::npos) {
						int pos = value.find(".");
						value.erase(pos);
					}
					i->value = value;
				}
			}
		}
		if(!find) cout << "[Error] \"" << tmp << "\" variable not found!\n";
	}
}

//For Test.
void BigN::showVariale() {
	vector<Variable>::iterator i;
	cout << "\n================================\n";
	cout << "Type\tName\tValue\n";
	for (i = list.begin(); i != list.end(); i++) {
		cout << i->dataType << "\t" << i->name << "\t" << i->value << "\n";
	}
	cout << "================================\n\n";
}