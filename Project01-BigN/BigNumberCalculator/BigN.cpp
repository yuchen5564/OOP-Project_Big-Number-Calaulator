// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/27

//class函式內容

//2022.04.27 [新增]分數運算

#include "BigN.h"

string BigN::countValue(string _in) {
	bool errorCode = 0;
	int len = _in.length();
	int count = 0;
	string result;
	//2022.04.23 [新增] 去除不必要的空格，以避免後續判讀出問題
	for (int i = 0; i < len; i++) {
		if (_in[i] == ' ') {
			_in.erase(i, 1);
			len--;
		}
		if (_in[i] == '(' || _in[i] == ')') count++;
	}

	//檢查括號 --2022.04.25
	if (count % 2 != 0) {
		errorCode = 1;
		ERROR("Parentheses are not paired!");
		//cout << "[Error] Parentheses are not paired!\n";
	}

	//算式不合法
	if (_in[0] == '*' || _in[0] == '/' || _in[0] == '^' || _in[0] == '!') {
		errorCode = 1;
		ERROR("Please confirm the formula!");
		//cout << "[Error] Please confirm the formula!\n";
	}
	//cout << _in << endl;
	if (_in.find("=") != string::npos) { //2022.04.22 [新增] 防呆，輸入結尾有=
				
		_in.erase(_in.find("="), 1);
		//return result;
	}
	//cout << _in << endl;

	if (!errorCode) {
		string postfix = infix2posfix(_in);
		//cout << postfix << endl;
		//cout << postfix << endl;
		istringstream in(postfix);
		stack<string> tmp;
		string s;// , result;// , s1, s2;
		Farction fa1, fa2, fa3;
		while (!errorCode && in >> s) {

			switch (sign(s)) {
			case 2:case 3:case 4:
				//2022.04.27 [新增] error code: 算式不合法(ex. 123+++)
				if (tmp.empty()) {
					errorCode = 1;
					ERROR("Please confirm the formula!");
					//cout << "[Error] Please confirm the formula!\n";
					break;
				}
				else {
					s2 = tmp.top();
					tmp.pop();
				}
				//2022.04.25 [新增] error code: 算式不合法(ex. 1*/3)
				if (tmp.empty()) {
					errorCode = 1;
					ERROR("Please confirm the formula!");
					//cout << "[Error] Please confirm the formula!\n";
					break;
				}
				else {
					s1 = tmp.top();
					tmp.pop();
				}
				
				//分數處裡
				if (s1.find("Farction") != string::npos && s2.find("Farction") != string::npos) {
					fa1 = findFarction(s1);
					fa2 = findFarction(s2);
					
					if (s == "+") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = add(multi(fa1.molecular, fa2.denominator), multi(fa2.molecular, fa1.denominator));
						//tmp.push(setFarction(fa3.molecular, fa3.denominator));
					}
					else if (s == "-") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = sub(multi(fa1.molecular, fa2.denominator), multi(fa2.molecular, fa1.denominator));
						//tmp.push(setFarction(fa3.molecular, fa3.denominator));
					}
					else if (s == "*") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = multi(fa1.molecular, fa2.molecular);
					}
					else if (s == "^") {
						string po = divide(fa2.molecular, fa2.denominator);
						if (po.find(".") != string::npos) {
							int poLen = po.length();
							if (po[poLen - 1] == '5' && po[poLen - 2] == '.') {
								fa3.molecular = power(fa1.molecular, po);
								fa3.denominator = power(fa1.denominator, po);
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
							}
						}
						else {
							fa3.molecular = power(fa1.molecular, po);
							fa3.denominator = power(fa1.denominator, po);
						}
					}
					tmp.push(setFarction(fa3.molecular, fa3.denominator));
				}
				else {
					if (s == "+") {
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if (s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						else {
							tmp.push(add(s1, s2));	//2022.04.17
						}

						//tmp.push(s1 + s2);
					}
					else if (s == "-") {
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if(s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						else {
							tmp.push(sub(s1, s2, 1));	//2022.04.17
						}
					}
					else if (s == "*") {
						tmp.push(multi(s1, s2)); //2022.04.18
					}
					else if (s == "/") {
						if (s2 == "0" || s2 == "0.0") { //2022.04.21 [新增] Error Code
							errorCode = 1;
							ERROR("Divisor cannot be zero!");
							//cout << "[Error] Divisor cannot be zero!\n";
						}
						else {
							if (s1.find("Farction") == string::npos) {
								tmp.push(setFarction(s1, s2));
								break;
							}
							else if (s1.find("Farction") != string::npos) {
								tmp.push(countFarction(s1, s, s2));
								//cout << tmp.top() << endl;
								break;
							}
							else {
								tmp.push(divide(s1, s2)); //2022.04.22 By ming.
							}

						}
					}
					else if (s == "^") {
						string result;
						//cout << s1 << " " << s2 << endl;
						if (s1.find("Farction") != string::npos) {
							if (s2.find("Farction") != string::npos) {
								fa2 = findFarction(s2);
								s2 = divide(fa2.molecular, fa2.denominator);
								cout << s2 << endl;
							}
							fa1 = findFarction(s1);
							result = power(fa1.molecular, s2);
							if (result != "illegal") {
								fa3.molecular = result;
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								break;
							}
							result = power(fa1.denominator, s2);
							if (result != "illegal") {
								fa3.denominator = result;
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								break;
							}
							tmp.push(setFarction(fa3.molecular,fa3.denominator));
						}
						else if (s2.find("Farction") != string::npos) {
							fa2 = findFarction(s2);
							s2 = divide(fa2.molecular, fa2.denominator);
							//cout << s2 << endl;
							result = power(s1, s2);
							if (result != "illegal") {
								tmp.push(result);
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								break;
							}
						}
						else {
							result = power(s1, s2);
							if (result != "illegal") tmp.push(power(s1, s2));
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								//cout << "[Error] The power must be a multiple of 0.5\n";
							}
						}
					}
				}
				break;
			case 5: //2022.04.20 [新增] Error Code: 階乘內有小數點、數字是負數
				s1 = tmp.top();
				tmp.pop();
				s1 = clear0(s1);
				if (s1.find("Farction") != string::npos) {
					fa3 = findFarction(s1);
					s1 = divide(fa3.molecular, fa3.denominator);
				}
				if (s1.find(".") != string::npos) { //2.0 ? allow
					ERROR("Factorial cannot have decimals!");
					//cout << "[Error] Factorial cannot have decimals!\n";
					errorCode = 1;
					break;
				}
				else if (s1[0] == '-') {
					ERROR("Factorial cannot be negative!");
					//cout << "[Error] Factorial cannot be negative!\n";
					errorCode = 1;
					break;
				}
				else {
					tmp.push(fac(s1));
				}
				break;
			default:
				//if (s == "=") break;
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
				if (flag) tmp.push(s);
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
						ERROR("\"" + s + "\" variable not found!");
						//cout << "[Error] \"" << s << "\" variable not found!\n";
						errorCode = 1;
					}
				}
				break;
			}
		}
		if (!errorCode) {
			if (tmp.top().find("Farction") == string::npos) {
				return tmp.top();
			}
			else {
				Farction fa = findFarction(tmp.top());
				return divide(fa.molecular, fa.denominator);
			}
		}	
	}
	return "Error";
}

void BigN::setVariale(string _in) {

	bool errorCode = 0;
	
	//字元分隔
	_in = splitString(_in);
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

				//去除不合型別的部分
				if (var.dataType == "Integer") checkInteger(&var.value);

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
			errorCode = 1;
			ERROR("Data type not found!");
			//cout << "[Error] Data type not found!\n";
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
		if (!find) {
			ERROR("\"" + tmp + "\" variable not found!");
			errorCode = 1;
		}
		
		
		 //cout << "[Error] \"" << tmp << "\" variable not found!\n";
	}
	//2022.04.27 [修改] 輸出列表時機
	if (!errorCode) showVariale();
}

//For Test.
void BigN::showVariale() {
	vector<Variable>::iterator i;
	SET_COLOR(14);
	cout << "=====Now in memory======\n";
	cout << "Type\tName\tValue\n";
	cout << "------------------------\n";
	for (i = list.begin(); i != list.end(); i++) {
		cout << i->dataType << "\t" << i->name << "\t" << i->value << "\n";
	}
	cout << "========================\n";
	SET_COLOR(15);
	
}

string BigN::setFarction(string molecular, string denominator){
	Farction tmp;
	tmp.denominator = denominator;
	tmp.molecular = molecular;
	tmp.name = "Farction" + to_string(farctIndex);
	//cout << tmp.name<<" "<<tmp.molecular << " " << tmp.denominator << endl;
	farct.push_back(tmp);
	farctIndex++;
	return tmp.name;
}

Farction BigN::findFarction(string name){
	Farction tmp;
	vector<Farction>::iterator i;
	for (i = farct.begin(); i != farct.end(); i++) {
		if (name == i->name) {
			tmp = *i;
			break;
		}
	}
	return tmp;
}

string BigN::countFarction(string name, string op, string s2){
	//cout << s2 << endl;
	Farction tmp = findFarction(name);
	switch (op[0]){
	case'+':
		s2 = multi(tmp.denominator, s2);
		tmp.molecular = add(tmp.molecular, s2);
		break;
	case'-':
		s2 = multi(tmp.denominator, s2);
		tmp.molecular = sub(tmp.molecular, s2, 1);
		if (s2 == "0") {
			tmp.molecular = '-' + tmp.molecular;
		}
		break;
	case'/':
		tmp.denominator = multi(tmp.denominator, s2);
	}
	//cout << tmp.molecular << " " << tmp.denominator << endl;
	return setFarction(tmp.molecular, tmp.denominator);
}
