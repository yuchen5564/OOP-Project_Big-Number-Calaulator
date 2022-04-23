// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/23                  

//�x�s���

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

//2022.04.21 [�״_] ���t��error���D �B ======> [�ݳB�z] * / �b���쨾�b 
string infix2posfix(string _infix) {
	//2022.04.22 [�s�W] ��J�L�Ů�A�����j�B�⤸�P����
	int len = _infix.length();
	bool f = 0;
	for (int i = 0; i < len; i++) {
		//2022.04.23 [�ץ�] �J��t�����|���j
		if (!isdigit(_infix[i])) {
			if (f) {
				f = 0;
				continue;
			}

			if (_infix[i] == '(') f = 1;
			else f = 0;
			/*if (_infix[i] == '-' && isdigit(_infix[i + 1])) {
				continue;
			}*/
			_infix.insert(i, " ");
			i++;
			len++;
			_infix.insert(i + 1, " ");
			i++;
			len++;
		}
	}
	cout << _infix << endl;
	istringstream in(_infix);
	stack<string> tmp; //�Ȧs�B�⤸
	stack<string>postfix;
	string s;
	string result = {};
	vector<string>element;
	vector<string>::iterator i;
	//�����J�Ҧ�����
	while (in >> s) {
		element.push_back(s);
	}
	int ssign = 0;//0:+ ; 1:- //�������t���аO
	string snext; //�x�s�U�@�Ӥ���
	int count = 0; //�Ϥ����t���M�[��

	for (i = element.begin(); i != element.end(); i++) {
		s = *i;
		if (i != element.end() - 1) {
			snext = *(i + 1);
		}
		bool flag = 0;
		switch (sign(s)) {
		case 2: 
			//���t���B�z
			if (i != element.begin() && count == 0) {
				count++;
			}
			else {
				flag = 1;
				if (!(isdigit(snext[0]) || isdigit(snext[1]))) {
					if (s == "-" && ssign == 0) ssign = 1;
					else if (s == "-" && ssign == 1) ssign = 0;
					continue;
				}
			}
		case 3: case 4: case 5:
			if (s == "*" && tmp.top() == "/") { //2022.04.23 [�ץ�] 1/3*3 = 0.99999...
				string v = postfix.top();
				postfix.pop();
				postfix.push(snext);
				postfix.push(s);
				postfix.push(v);
				i++;
				break;
			}
			while (!tmp.empty() && sign(tmp.top()) >= sign(s)) {
				postfix.push(tmp.top());
				//result += ' ';
				//result += tmp.top();
				tmp.pop();
			}
			if (!flag) tmp.push(s);
			
			break;
		case 0:	// "("
			tmp.push(s);
			break;
		case 1:	// ")"
			while (tmp.top() != "(") {
				postfix.push(tmp.top());
				/*result += ' ';
				result += tmp.top();*/
				
				tmp.pop();
			}
			tmp.pop();
			break;
		case 999: //�D�B��Ÿ�
			//�B�z���t��
			if (ssign == 1 && s[0] != '-')	s = '-' + s;
			else if (ssign == 1 && s[0] == '-') s.erase(0, 1);
			ssign = 0; //�O�����m
			count = 0; //�O�����m
			postfix.push(s);
			/*result += ' ';
			result += s;*/
			
			break;
		}
		//result += ' ';
	}
	while (!tmp.empty()) {
		postfix.push(tmp.top());
		/*result += ' ';
		result += tmp.top();*/
		tmp.pop();
	}
	while (!postfix.empty()) {
		result =  postfix.top() + ' ' + result;
		postfix.pop();
	}
	cout << result << endl;
	return result;
}

//��0 --20220420����J�覡�A�Ϩ�i�H�B�z�p�ƹ��
void fill0(string* s1, string* s2) {
	int len1 = s1->length();
	int len2 = s2->length();
	//���S���p���I
	if (s1->find(".") == string::npos && s2->find(".") == string::npos) {
		if (len1 > len2) {
			for (int i = 0; i < len1 - len2; i++) {
				*s2 = '0' + *s2;
			}
		}
		else {
			for (int i = 0; i < len2 - len1; i++) {
				*s1 = '0' + *s1;
			}
		}
	}
	else {
		int dec1 = 0, dec2 = 0;
		if (s1->find(".") != string::npos) dec1 = s1->find(".");
		else {
			*s1 = *s1 + '.';
			dec1 = len1;
			len1++;
		}
		if (s2->find(".") != string::npos) dec2 = s2->find(".");
		else {
			*s2 = *s2 + '.';
			dec2 = len2;
			len2++;
		}

		//�ɻ���Ʀ�
		if (dec1 > dec2) {
			for (int i = 0; i < dec1 - dec2; i++) {
				*s2 = '0' + *s2;
			}
		}
		else {
			for (int i = 0; i < dec2 - dec1; i++) {
				*s1 = '0' + *s1;
			}
		}

		//�ɻ��p�Ʀ�
		dec1 = len1 - dec1;
		dec2 = len2 - dec2;
		if (dec1 > dec2) {
			for (int i = 0; i < dec1 - dec2; i++) {
				*s2 = *s2 + '0';
			}
		}
		else {
			for (int i = 0; i < dec2 - dec1; i++) {
				*s1 = *s1 + '0';
			}
		}
	}

}

//�w�B�̤p�Ƴ���(yuchen @ 2022.04.20)
//2022.04.21 [�׸�] �Y��Ʀ�۴�ᬰ0�A����0
string clear0(string s) {
	int len = s.length();
	int count = 0;
	//�B�̫e��L�N�q0
	for (int i = 0; i < len; i++) {
		if (s[i] == '-') continue;
		if (s[i] != '0') break;
		else count++;
	}
	//if (count == len) s = "0";
	if (s[0] == '-') s.erase(1, count);
	else s.erase(0, count);

	//�M��p���I�A�B�z���L�N�q0
	if (s.find(".") != string::npos) {
		count = 0;
		len = s.length();
		for (int i = len - 1; i >= 0; i--) {
			if (s[i] != '0') break;
			else count++;
		}
		//cout << "====" << count << endl;
		s.erase(len - count, count);
		len = s.length();
		if (s[len - 1] == '.') s.erase(len - 1, 1);
	}
	if (s[0] == '-' && s[1] == '.') { //2022.04.21 [�׸�] �Y��Ʀ�۴�ᬰ0�A����0
		s = '-' + s;
		s[1] = '0';
	}
	if (s[0] == '.') s = '0' + s; 
	if (s.length() == 0) s = "0"; //2022.04.21 [�׸�] �۴�ᵥ��0�A��X0
	return s;
}

//�w�B�̤p�Ƴ���(yuchen @ 2022.04.20)
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
	fill0(&s1, &s2);
	len = s1.length();

	for (int i = len - 1; i >= 0; i--) {
		if (s1[i] == '.' && s2[i] == '.') {
			result = '.' + result;
			continue;
		}
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
	return clear0(result)	;
}

//�w�B�̤p�Ƴ���(yuchen @ 2022.04.20)
string sub(string s1, string s2) {
	string result = {};
	bool sign = 0;
	if (s1[0] == '-' && s2[0] != '-') {
		s1.erase(0, 1);
		result = add(s2, s1);
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
	fill0(&s1, &s2);
	len = s1.length();

	for (int i = len - 1; i >= 0; i--) {
		if (s1[i] == '.' && s2[i] == '.') {
			result = '.' + result;
			continue;
		}
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

	//�t�ƳB�z
	if (borrow == 1) {
		for (int i = 0; i < len; i++) {
			if (s1[i] == '.' && s2[i] == '.') continue;
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

//�w�B�̤p�Ƴ���(yuchen @ 2022.04.20)
string multi(string s1, string s2) {
	bool sign = 0;
	if (s1[0] == '-' && s2[0] != '-') {
		sign = 1;
		s1.erase(0, 1);
	}
	else if (s2[0] == '-' && s1[0] != '-') {
		sign = 1;
		s2.erase(0, 1);
	}
	else if (s1[0] == '-' && s2[0] == '-') {
		s1.erase(0, 1);
		s2.erase(0, 1);
	}

	//�p��
	int dec = 0;
	int len1 = s1.length();
	int len2 = s2.length();
	if (s1.find(".") != string::npos) {
		dec += (len1 - s1.find(".") - 1);
		s1.erase(s1.find("."), 1);
		len1 = s1.length();
	}
	if (s2.find(".") != string::npos) {
		dec += (len2 - s2.find(".") - 1);
		s2.erase(s2.find("."), 1);
		len2 = s2.length();
	}

	//���k�p��
	int* tmp = new int[len1 + len2]{};
	for (int i = 0; i < len2; i++) {
		for (int j = 0; j < len1; j++) {
			tmp[i + j + 1] += (s1[j] - '0') * (s2[i] - '0');
		}
	}

	//�B�z�i��
	int carry = 0;
	for (int i = len1 + len2 - 1; i >= 0; i--) {
		tmp[i] += carry;
		if (tmp[i] >= 10) {
			carry = tmp[i] / 10;
			tmp[i] = tmp[i] % 10;
		}
		else {
			carry = 0;
		}
	}

	//�٭즨�r��
	string result = {};
	for (int i = 0; i < len1 + len2; i++) {
		result = result + (char)(tmp[i] + '0');
	}
	result = clear0(result);

	//�p���I
	if (dec != 0) {
		int len = result.length();
		result.insert(len - dec, ".");
	}
	if (sign) result = '-' + result;

	delete[] tmp;
	return clear0(result);
}

//���k�Ψ�========================================================
void dec2int(string& s1, string& s2)
{
	int s1DecimalLen = 0;
	int s2DecimalLen = 0;
	if (s1.find('.') == string::npos)
	{
		s1DecimalLen = 0;
	}
	else
	{
		s1DecimalLen = s1.size() - s1.find('.') - 1;
		s1.erase(s1.find('.'), 1);
	}

	if (s2.find('.') == string::npos)
	{
		s2DecimalLen = 0;
	}
	else
	{
		s2DecimalLen = s2.size() - s2.find('.') - 1;
		s2.erase(s2.find('.'), 1);
	}
	int maxDeciLen = s1DecimalLen > s2DecimalLen ? s1DecimalLen : s2DecimalLen;
	// �ɹs�ܾ��
	for (int i = 0; i < maxDeciLen - s1DecimalLen; i++)
	{
		s1 += "0";
	}
	for (int i = 0; i < maxDeciLen - s2DecimalLen; i++)
	{
		s2 += "0";
	}

}

//�C���U��@��s1�N�ɹs
string decimal100(string s1, string s2)
{
	string deciResult = "";
	string preS1 = s1;
	for (int i = 0; i < 100; i++)
	{
		s1 += "0";
		int dCounter = -1;
		while (s1[0] != '-')
		{
			preS1 = s1;
			s1 = sub(s1, s2);
			dCounter++;
		}
		s1 = preS1;
		char temp = dCounter + '0';
		deciResult += temp;
	}

	return deciResult;
}

//�w�B�z�p�Ƴ���(ming @ 2022.04.21)
string divide(string s1, string s2)
{
	// �P�_result���t��flag
	int flag = 0;
	if (s1[0] == '-' && s2[0] != '-')
	{
		flag = 1;
		s1.erase(0, 1);
	}
	else if (s1[0] != '-' && s2[0] == '-')
	{
		flag = 1;
		s2.erase(0, 1);
	}
	else if (s1[0] == '-' && s2[0] == '-')
	{
		s1.erase(0, 1);
		s2.erase(0, 1);
	}

	dec2int(s1, s2);

	// �M���h�l��0
	s1 = clear0(s1);
	s2 = clear0(s2);

	// �s���k��counter
	int counter = -1;
	// �Q���ƪ�temp
	string s1Temp = s1;
	// �W�@�ӳQ���ƪ�temp    for �Q���ƪ��פj�󰣼ƪ���
	string s1TempPre = s1;
	// �Q����(s1), ����(s2)������
	int s1Len = s1.size(), s2Len = s2.size();
	// result 
	string result = "";

	// ������� // ����decimal100
	if (s1Len < s2Len) result = "0." + decimal100(s1, s2);

	// ���׬ۦP���p
	else if (s1Len == s2Len)
	{
		// ����decimal100
		if (sub(s1, s2)[0] == '-')  result = "0." + decimal100(s1, s2);
		else
		{
			string preS1 = s1;
			// ���X�{�t����			
			while (s1[0] != '-')
			{
				preS1 = s1;
				s1 = sub(s1, s2);
				counter++;
			}
			// ��counter �[�Jresult
			char temp = counter + '0';
			result += temp;
			// �p��p�Ƴ���
			result += '.' + decimal100(preS1, s2); // �ɤp���I
		}
	}
	// �Q���ƪ���>���ƪ���
	else
	{
		// ���Ƹɹs�ܻP�Q���ƬۦP ex: 5 - 3
		int fill0Counter = s1.size() - s2.size(); // 2
		for (int i = 0; i < fill0Counter; i++)
		{
			s2 += "0";
		}
		// ����Q���ƥX�{�t�ƥB�h���ɹL���s����
		while (fill0Counter >= 0)
		{
			counter = -1;
			while (s1Temp[0] != '-')
			{
				// �s�Us1TempPre�p��0���e����
				s1TempPre = s1Temp;
				s1Temp = sub(s1Temp, s2);
				counter++;
			}
			// ��counter �[�Jresult
			char temp = counter + '0';
			result += temp;
			// s1�^��p��0���e����
			s1Temp = s1TempPre;
			//�h�@�ӹs
			if (fill0Counter > 0) s2.erase(s2.end() - 1);
			fill0Counter--;
		}
		result += "." + decimal100(s1TempPre, s2);
	}
	// result�[�W���t�� // �Y�t���N�e���['-' ����do nothing
	if (flag == 1) result = "-" + result;
	return clear0(result);
}

//����(�ɤO��) --> TLE?�ֳt��k?
//2022.04.21 [����] 3000! 45s; 5000! 3min20s
string fac(string s1) {
	if (s1 == "0") return "1"; //2022.04.22 [�s�W] 0!�w�q
	string result = s1;
	s1 = sub(s1, "1");
	while (s1 != "1") {
		result = multi(result, s1);
		s1 = sub(s1, "1");
	}
	return result;
}


