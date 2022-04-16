// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/15

//class�禡���e

#include "BigN.h"

// �B��l�u���v
// ��J: �ƭȦr��ιB��l�r��
// ��^: �����u���v�Ʀr�A�Y�D�B��l��^0
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

// ���Ǧ����Ǧ�
// ��J: ���Ǧ��r��A�C�ӼƩM�Ÿ������n���@�ӪŮ�(e.g. 1+2+3: 1 + 2 + 3)
// ��^: ��Ǧ��r��A�C�ӼƩM�Ÿ������|���@�ӪŮ�(e.g. 12+3+: 1 2 + 3 +)
string infix2posfix(string _infix) {
	istringstream in(_infix);
	stack<string> tmp; //�Ȧs�B�⤸
	stack<string> postfix; //�x�s�ഫ��榡
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
