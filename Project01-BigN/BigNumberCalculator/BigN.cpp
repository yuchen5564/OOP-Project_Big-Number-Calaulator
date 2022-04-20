// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/20

//class函式內容

#include "BigN.h"

void BigN::countValue(string _in) {
	bool errorCode = 0;
	string postfix = infix2posfix(_in);
	istringstream in(postfix);
	stack<string> tmp;
	string s, result, s1, s2;
	while (in >> s) {
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
			tmp.push(s);
			break;
		}
	}
	if (!errorCode) {
		cout << tmp.top() << endl;
		tmp.pop();
	}
	
}

void BigN::setValue(string _in) {

}