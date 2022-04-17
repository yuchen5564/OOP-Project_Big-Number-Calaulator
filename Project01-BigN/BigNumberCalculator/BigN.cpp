// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/17

//class¨ç¦¡¤º®e

#include "BigN.h"

void BigN::countValue(string _in) {
	string postfix = infix2posfix(_in);
	cout << postfix << endl;
	istringstream in(postfix);
	stack<string> tmp;
	string s, result, s1, s2;
	while (in >> s) {
		switch (sign(s)) {
		case 2:case 3:case 4:case 5:
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

			}
			else if (s == "/") {

			}
			else if (s == "^") {

			}
			else if (s == "!") {

			}
			break;
		default:
			tmp.push(s);
			break;
		}
	}
	cout << tmp.top() << endl;
	tmp.pop();
}