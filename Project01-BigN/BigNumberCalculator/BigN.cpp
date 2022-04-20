// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

//class函式內容

#include "BigN.h"

void BigN::countValue(string _in) {
	bool errorCode = 0;
	string postfix = infix2posfix(_in);
	istringstream in(postfix);
	stack<string> tmp;
	string s, result, s1, s2;
	while (in >> s) {
		if (errorCode) break;
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
				tmp.push(divide(s1, s2)); //2022.04.20 By ming.
			}
			else if (s == "^") {

			}
			break;
		case 5: //階乘只有一個運算數字 //2022.04.20
			s1 = tmp.top();
			tmp.pop();
			if (s1.find(".") != string::npos) {
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
						cout <<s<<" "<< i->value << endl;
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
	if (!errorCode) {
		cout << "Value: " << tmp.top() << endl;
		tmp.pop();
	}
	
}


void BigN::setVariale(string _in) {
	//接收資料
	stringstream in(_in);
	string tmp;
	in >> tmp;
	Variable var;
	in >> tmp;
	var.dataType = tmp;
	in >> tmp;
	var.name = tmp;
	in >> tmp;
	in >> tmp;
	var.value = tmp;

	if (var.dataType == "Integer" || var.dataType == "Decimal") {
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
	else {
		cout << "[Error] Data type not found!\n";
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
}