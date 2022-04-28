// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/27

//class函式內容

//2022.04.27 [新增] 分數運算
//2022.04.28 [新增] 輸出小數100位

#include "BigN.h"

//輸入若有小數，輸出也要有小數100位
void fill100(string* s) {

	//尋找小數點
	if (s->find(".") == string::npos) {
		*s = *s + '.';
	}

	int dec = s->find(".");
	int len = s->length();

	//補0
	for (int i = 0; i < 100-(len - dec - 1); i++) {
		*s = *s + '0';
	}
}

string BigN::countValue(string _in) {
	bool decPoint = 0; //紀錄是否有小數點出現
	bool errorCode = 0; //紀錄是否有error出現
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
	}

	//算式不合法
	if (_in[0] == '*' || _in[0] == '/' || _in[0] == '^' || _in[0] == '!') {
		errorCode = 1;
		ERROR("Please confirm the formula!");
	}

	//去除結尾=
	if (_in.find("=") != string::npos) { //2022.04.22 [新增] 防呆，輸入結尾有=		
		_in.erase(_in.find("="), 1);
	}

	//開始計算
	if (!errorCode) {
		string postfix = infix2posfix(_in); //轉換為後序式
		istringstream in(postfix); //接收輸入
		stack<string> tmp; //暫存stack
		string s; //目前輸入
		Farction fa1, fa2, fa3; //暫存分數

		while (!errorCode && in >> s) {

			//紀錄算式中是否有小數點出現，若有需補齊小數位數100位
			if (s.find(".") != string::npos) decPoint = 1;

			//分析當前輸入
			switch (sign(s)) {
			case 2:case 3:case 4: //輸入: +-*/^

				//算式不合法
				//2022.04.27 [新增] error code: 算式不合法(ex. 123+++)
				if (tmp.empty()) {
					errorCode = 1;
					ERROR("Please confirm the formula!");
					break;
				}
				else {
					s2 = tmp.top(); //接收第一個數
					tmp.pop();
				}

				//算式不合法
				//2022.04.25 [新增] error code: 算式不合法(ex. 1*/3)
				if (tmp.empty()) {
					errorCode = 1;
					ERROR("Please confirm the formula!");
					break;
				}
				else {
					s1 = tmp.top(); //接收第二個數
					tmp.pop();
				}
				
				//分數處理(兩個數都是分數)
				if (s1.find("Farction") != string::npos && s2.find("Farction") != string::npos) {
					fa1 = findFarction(s1);
					fa2 = findFarction(s2);
					
					//運算+
					if (s == "+") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = add(multi(fa1.molecular, fa2.denominator), multi(fa2.molecular, fa1.denominator));
						//tmp.push(setFarction(fa3.molecular, fa3.denominator));
					}
					//運算-
					else if (s == "-") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = sub(multi(fa1.molecular, fa2.denominator), multi(fa2.molecular, fa1.denominator));
						//tmp.push(setFarction(fa3.molecular, fa3.denominator));
					}
					//運算*
					else if (s == "*") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = multi(fa1.molecular, fa2.molecular);
					}
					//運算^
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
				//其餘運算(都不是分數、其中一個是分數)
				else {

					//運算+
					if (s == "+") {

						//其中一個數是分數
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if (s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						//都不是分數
						else {
							tmp.push(add(s1, s2));	//2022.04.17
						}

					}
					//運算-
					else if (s == "-") {

						//其中一個數是分數
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if(s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						//都不是分數
						else {
							tmp.push(sub(s1, s2, 1));	//2022.04.17
						}

					}
					//運算*
					else if (s == "*") {

						//其中一個數是分數
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if (s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						//都不是分數
						else {
							tmp.push(multi(s1, s2)); //2022.04.18
						}

					}
					//運算/
					else if (s == "/") {

						//如果分母是0，輸出Error
						if (s2 == "0" || s2 == "0.0") { //2022.04.21 [新增] Error Code
							errorCode = 1;
							ERROR("Divisor cannot be zero!");
							//cout << "[Error] Divisor cannot be zero!\n";
						}
						//分母不是0
						else {
							
							//其中一個數是分數
							if (s1.find("Farction") == string::npos) {
								tmp.push(setFarction(s1, s2));
								break;
							}
							else if (s1.find("Farction") != string::npos) {
								tmp.push(countFarction(s1, s, s2));
								break;
							}
							//都不是分數
							else {
								tmp.push(divide(s1, s2)); //2022.04.22 By ming.
							}

						}

					}
					//運算^
					else if (s == "^") {
						string result;

						//其中一個數是分數
						if (s1.find("Farction") != string::npos) {

							//另一數也是分數
							if (s2.find("Farction") != string::npos) {
								fa2 = findFarction(s2);
								s2 = divide(fa2.molecular, fa2.denominator);
								cout << s2 << endl;
							}

							fa1 = findFarction(s1);

							//計算分子
							result = power(fa1.molecular, s2); 

							//輸入不合法
							if (result != "illegal") {
								fa3.molecular = result;
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								break;
							}

							//計算分母
							result = power(fa1.denominator, s2);

							//輸入不合法
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

							//計算
							result = power(s1, s2);

							//輸入不合法
							if (result != "illegal") {
								tmp.push(result);
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								break;
							}

						}
						//都不是分數
						else {
							result = power(s1, s2);

							//輸入不合法
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
			case 5: //輸入! //2022.04.20 [新增] Error Code: 階乘內有小數點、數字是負數
				s1 = tmp.top();
				tmp.pop();
				s1 = clear0(s1);

				//是分數
				if (s1.find("Farction") != string::npos) {
					fa3 = findFarction(s1);
					s1 = divide(fa3.molecular, fa3.denominator);
				}

				//不允許小數點
				if (s1.find(".") != string::npos) { //2.0 ? allow
					ERROR("Factorial cannot have decimals!");
					errorCode = 1;
					break;
				}
				//不允許負數
				else if (s1[0] == '-') {
					ERROR("Factorial cannot be negative!");
					errorCode = 1;
					break;
				}
				//正常計算
				else {
					tmp.push(fac(s1));
				}

				break;
			default: //輸入不是符號

				//清除開頭+
				if (s[0] == '+') s.erase(0, 1);

				int len = s.length();
				bool flag = 1;

				//判斷是否有非數字字元
				for (int i = 0; i < len; i++) {
					if (s[0] == '-') break;
					if (s.find(".") != string::npos) break;
					if (!isdigit(s[i])) {
						flag = 0;
						break;
					}
				}

				//都是數字，放入堆疊
				if (flag) tmp.push(s);
				//非全數字，檢查變數
				else {
					vector<Variable>::iterator i;
					flag = 0;

					//尋訪變數
					for (i = list.begin(); i != list.end(); i++) {

						//找到
						if (s == i->name) {
							s = i->value;
							flag = 1;
							break;
						}

					}

					//有找到
					if (flag) tmp.push(s);
					//沒找到
					else {
						ERROR("\"" + s + "\" variable not found!");
						//cout << "[Error] \"" << s << "\" variable not found!\n";
						errorCode = 1;
					}

				}

				break;
			}

		}

		string t;

		//回傳(沒有error)
		if (!errorCode) {

			//非分數
			if (tmp.top().find("Farction") == string::npos) {

				//有出現過小數點
				if (decPoint) {
					t = tmp.top();
					fill100(&t);
					return t;
				}
				else {
					return tmp.top();
				}

			}
			//是分數
			else {
				Farction fa = findFarction(tmp.top());
				t = divide(fa.molecular, fa.denominator);

				//有出現過小數點
				if (decPoint) fill100(&t);
				//本身有小數點
				else if (t.find(".") != string::npos) fill100(&t);

				return t;
			}

		}	
	}
	
	//回傳(有Error)
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
	
	//輸入
	in >> tmp;

	//輸入: Set Integer/Decimal A = 10
	if (tmp == "Set") { 

		//接收其他資訊
		in >> tmp;
		var.dataType = tmp;
		in >> tmp;
		var.name = tmp;
		in >> tmp;

		while (in >> tmp) {
			value += (' ' + tmp);
		}

		//型別正確
		if (var.dataType == "Integer" || var.dataType == "Decimal") {
			var.value = countValue(value); //計算數值

			if (var.value != "Error") {
				
				//去除不合型別的部分
				if (var.dataType == "Integer") checkInteger(&var.value);

				//尋找是否已存在
				bool find = 0;
				vector<Variable>::iterator i;

				for (i = list.begin(); i != list.end(); i++) {

					//有找到
					if (var.name == i->name) {
						i->dataType = var.dataType;
						i->value = var.value;
						find = 1;
					}

				}

				//未找到
				if (!find) list.push_back(var);
			}
		}
		//有錯誤
		else {
			errorCode = 1;
			ERROR("Data type not found!");
		}

	}
	//輸入: A = 10 + 5 || A = A + A
	else { 
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
				break;	//2022.04.28 [修正] 給值問題
			}
		}
		if (!find) {
			ERROR("\"" + tmp + "\" variable not found!");
			errorCode = 1;
		}
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
	return setFarction(tmp.molecular, tmp.denominator);
}
