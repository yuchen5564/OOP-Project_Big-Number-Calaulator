// File: BigN.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/27

//class�禡���e

//2022.04.27 [�s�W] ���ƹB��
//2022.04.28 [�s�W] ��X�p��100��

#include "BigN.h"

//��J�Y���p�ơA��X�]�n���p��100��
void fill100(string* s) {

	//�M��p���I
	if (s->find(".") == string::npos) {
		*s = *s + '.';
	}

	int dec = s->find(".");
	int len = s->length();

	//��0
	for (int i = 0; i < 100-(len - dec - 1); i++) {
		*s = *s + '0';
	}
}

string BigN::countValue(string _in) {
	bool decPoint = 0; //�����O�_���p���I�X�{
	bool errorCode = 0; //�����O�_��error�X�{
	int len = _in.length();
	int count = 0;
	string result;

	//2022.04.23 [�s�W] �h�������n���Ů�A�H�קK����PŪ�X���D
	for (int i = 0; i < len; i++) {
		if (_in[i] == ' ') {
			_in.erase(i, 1);
			len--;
		}
		if (_in[i] == '(' || _in[i] == ')') count++;
	}

	//�ˬd�A�� --2022.04.25
	if (count % 2 != 0) {
		errorCode = 1;
		ERROR("Parentheses are not paired!");
	}

	//�⦡���X�k
	if (_in[0] == '*' || _in[0] == '/' || _in[0] == '^' || _in[0] == '!') {
		errorCode = 1;
		ERROR("Please confirm the formula!");
	}

	//�h������=
	if (_in.find("=") != string::npos) { //2022.04.22 [�s�W] ���b�A��J������=		
		_in.erase(_in.find("="), 1);
	}

	//�}�l�p��
	if (!errorCode) {
		string postfix = infix2posfix(_in); //�ഫ����Ǧ�
		istringstream in(postfix); //������J
		stack<string> tmp; //�Ȧsstack
		string s; //�ثe��J
		Farction fa1, fa2, fa3; //�Ȧs����

		while (!errorCode && in >> s) {

			//�����⦡���O�_���p���I�X�{�A�Y���ݸɻ��p�Ʀ��100��
			if (s.find(".") != string::npos) decPoint = 1;

			//���R��e��J
			switch (sign(s)) {
			case 2:case 3:case 4: //��J: +-*/^

				//�⦡���X�k
				//2022.04.27 [�s�W] error code: �⦡���X�k(ex. 123+++)
				if (tmp.empty()) {
					errorCode = 1;
					ERROR("Please confirm the formula!");
					break;
				}
				else {
					s2 = tmp.top(); //�����Ĥ@�Ӽ�
					tmp.pop();
				}

				//�⦡���X�k
				//2022.04.25 [�s�W] error code: �⦡���X�k(ex. 1*/3)
				if (tmp.empty()) {
					errorCode = 1;
					ERROR("Please confirm the formula!");
					break;
				}
				else {
					s1 = tmp.top(); //�����ĤG�Ӽ�
					tmp.pop();
				}
				
				//���ƳB�z(��ӼƳ��O����)
				if (s1.find("Farction") != string::npos && s2.find("Farction") != string::npos) {
					fa1 = findFarction(s1);
					fa2 = findFarction(s2);
					
					//�B��+
					if (s == "+") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = add(multi(fa1.molecular, fa2.denominator), multi(fa2.molecular, fa1.denominator));
						//tmp.push(setFarction(fa3.molecular, fa3.denominator));
					}
					//�B��-
					else if (s == "-") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = sub(multi(fa1.molecular, fa2.denominator), multi(fa2.molecular, fa1.denominator));
						//tmp.push(setFarction(fa3.molecular, fa3.denominator));
					}
					//�B��*
					else if (s == "*") {
						fa3.denominator = multi(fa1.denominator, fa2.denominator);
						fa3.molecular = multi(fa1.molecular, fa2.molecular);
					}
					//�B��^
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
				//��l�B��(�����O���ơB�䤤�@�ӬO����)
				else {

					//�B��+
					if (s == "+") {

						//�䤤�@�ӼƬO����
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if (s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						//�����O����
						else {
							tmp.push(add(s1, s2));	//2022.04.17
						}

					}
					//�B��-
					else if (s == "-") {

						//�䤤�@�ӼƬO����
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if(s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						//�����O����
						else {
							tmp.push(sub(s1, s2, 1));	//2022.04.17
						}

					}
					//�B��*
					else if (s == "*") {

						//�䤤�@�ӼƬO����
						if (s1.find("Farction") != string::npos) {
							tmp.push(countFarction(s1, s, s2));
						}
						else if (s2.find("Farction") != string::npos) {
							tmp.push(countFarction(s2, s, s1));
						}
						//�����O����
						else {
							tmp.push(multi(s1, s2)); //2022.04.18
						}

					}
					//�B��/
					else if (s == "/") {

						//�p�G�����O0�A��XError
						if (s2 == "0" || s2 == "0.0") { //2022.04.21 [�s�W] Error Code
							errorCode = 1;
							ERROR("Divisor cannot be zero!");
							//cout << "[Error] Divisor cannot be zero!\n";
						}
						//�������O0
						else {
							
							//�䤤�@�ӼƬO����
							if (s1.find("Farction") == string::npos) {
								tmp.push(setFarction(s1, s2));
								break;
							}
							else if (s1.find("Farction") != string::npos) {
								tmp.push(countFarction(s1, s, s2));
								break;
							}
							//�����O����
							else {
								tmp.push(divide(s1, s2)); //2022.04.22 By ming.
							}

						}

					}
					//�B��^
					else if (s == "^") {
						string result;

						//�䤤�@�ӼƬO����
						if (s1.find("Farction") != string::npos) {

							//�t�@�Ƥ]�O����
							if (s2.find("Farction") != string::npos) {
								fa2 = findFarction(s2);
								s2 = divide(fa2.molecular, fa2.denominator);
								cout << s2 << endl;
							}

							fa1 = findFarction(s1);

							//�p����l
							result = power(fa1.molecular, s2); 

							//��J���X�k
							if (result != "illegal") {
								fa3.molecular = result;
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								break;
							}

							//�p�����
							result = power(fa1.denominator, s2);

							//��J���X�k
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

							//�p��
							result = power(s1, s2);

							//��J���X�k
							if (result != "illegal") {
								tmp.push(result);
							}
							else {
								errorCode = 1;
								ERROR("The power must be a multiple of 0.5!");
								break;
							}

						}
						//�����O����
						else {
							result = power(s1, s2);

							//��J���X�k
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
			case 5: //��J! //2022.04.20 [�s�W] Error Code: ���������p���I�B�Ʀr�O�t��
				s1 = tmp.top();
				tmp.pop();
				s1 = clear0(s1);

				//�O����
				if (s1.find("Farction") != string::npos) {
					fa3 = findFarction(s1);
					s1 = divide(fa3.molecular, fa3.denominator);
				}

				//�����\�p���I
				if (s1.find(".") != string::npos) { //2.0 ? allow
					ERROR("Factorial cannot have decimals!");
					errorCode = 1;
					break;
				}
				//�����\�t��
				else if (s1[0] == '-') {
					ERROR("Factorial cannot be negative!");
					errorCode = 1;
					break;
				}
				//���`�p��
				else {
					tmp.push(fac(s1));
				}

				break;
			default: //��J���O�Ÿ�

				//�M���}�Y+
				if (s[0] == '+') s.erase(0, 1);

				int len = s.length();
				bool flag = 1;

				//�P�_�O�_���D�Ʀr�r��
				for (int i = 0; i < len; i++) {
					if (s[0] == '-') break;
					if (s.find(".") != string::npos) break;
					if (!isdigit(s[i])) {
						flag = 0;
						break;
					}
				}

				//���O�Ʀr�A��J���|
				if (flag) tmp.push(s);
				//�D���Ʀr�A�ˬd�ܼ�
				else {
					vector<Variable>::iterator i;
					flag = 0;

					//�M�X�ܼ�
					for (i = list.begin(); i != list.end(); i++) {

						//���
						if (s == i->name) {
							s = i->value;
							flag = 1;
							break;
						}

					}

					//�����
					if (flag) tmp.push(s);
					//�S���
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

		//�^��(�S��error)
		if (!errorCode) {

			//�D����
			if (tmp.top().find("Farction") == string::npos) {

				//���X�{�L�p���I
				if (decPoint) {
					t = tmp.top();
					fill100(&t);
					return t;
				}
				else {
					return tmp.top();
				}

			}
			//�O����
			else {
				Farction fa = findFarction(tmp.top());
				t = divide(fa.molecular, fa.denominator);

				//���X�{�L�p���I
				if (decPoint) fill100(&t);
				//�������p���I
				else if (t.find(".") != string::npos) fill100(&t);

				return t;
			}

		}	
	}
	
	//�^��(��Error)
	return "Error";
}


void BigN::setVariale(string _in) {
	bool errorCode = 0;
	
	//�r�����j
	_in = splitString(_in);

	//�������
	stringstream in(_in);
	string tmp;
	Variable var;
	string value = {};
	
	//��J
	in >> tmp;

	//��J: Set Integer/Decimal A = 10
	if (tmp == "Set") { 

		//������L��T
		in >> tmp;
		var.dataType = tmp;
		in >> tmp;
		var.name = tmp;
		in >> tmp;

		while (in >> tmp) {
			value += (' ' + tmp);
		}

		//���O���T
		if (var.dataType == "Integer" || var.dataType == "Decimal") {
			var.value = countValue(value); //�p��ƭ�

			if (var.value != "Error") {
				
				//�h�����X���O������
				if (var.dataType == "Integer") checkInteger(&var.value);

				//�M��O�_�w�s�b
				bool find = 0;
				vector<Variable>::iterator i;

				for (i = list.begin(); i != list.end(); i++) {

					//�����
					if (var.name == i->name) {
						i->dataType = var.dataType;
						i->value = var.value;
						find = 1;
					}

				}

				//�����
				if (!find) list.push_back(var);
			}
		}
		//�����~
		else {
			errorCode = 1;
			ERROR("Data type not found!");
		}

	}
	//��J: A = 10 + 5 || A = A + A
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
				break;	//2022.04.28 [�ץ�] ���Ȱ��D
			}
		}
		if (!find) {
			ERROR("\"" + tmp + "\" variable not found!");
			errorCode = 1;
		}
	}
	//2022.04.27 [�ק�] ��X�C��ɾ�
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
