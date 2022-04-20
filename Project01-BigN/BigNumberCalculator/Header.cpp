// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

//纗ㄧ计

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

string infix2posfix(string _infix) {
	//if (_infix == "") return "";
	istringstream in(_infix);
	stack<string> postfix;
	stack<string> tmp; //既笲衡じ
	string s;
	while (in >> s) {
		switch (sign(s)) {
		case 2:case 3: case 4: case 5:
			while (!tmp.empty() && sign(tmp.top()) >= sign(s)) {
				postfix.push(tmp.top());
				//result += tmp.top();
				tmp.pop();
			}
			tmp.push(s);
			break;
		case 0:	// "("
			tmp.push(s);
			break;
		case 1:	// ")"
			//cout << "." << endl;
			while (tmp.top() != "(") {
				postfix.push(tmp.top());
				//result += tmp.top();
				tmp.pop();
			}
			tmp.pop();
			break;
		case 999:
			postfix.push(s);
			//result += s;
			break;
		}
	}

	
	while (!tmp.empty()) {
		postfix.push(tmp.top());
		//result += tmp.top();
		tmp.pop();
	}
	string result = {};
	while (!postfix.empty()) {
		result = postfix.top() + " " + result;
		postfix.pop();
	}
	return result;
}

//干0 --20220420э块よΑㄏㄤ矪柑计癸霍
void fill0(string* s1, string* s2) {
	int len1 = s1->length();
	int len2 = s2->length();
	//常⊿Τ计翴
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

		//干霍俱计
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

		//干霍计
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

//矪柑计场だ(yuchen @ 2022.04.20)
string clear0(string s) {
	int len = s.length();
	int count = 0;
	//矪柑玡よ礚種竡0
	for (int i = 0; i < len; i++) {
		if (s[i] == '-') continue;
		if (s[i] != '0') break;
		else count++;
	}
	if (count == len) s = "0";
	else if (s[0] == '-') s.erase(1, count);
	else s.erase(0, count);

	//碝т计翴矪瞶よ礚種竡0
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

	return s;
}

//矪柑计场だ(yuchen @ 2022.04.20)
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

//矪柑计场だ(yuchen @ 2022.04.20)
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

	//璽计矪瞶
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

//矪柑计场だ(yuchen @ 2022.04.20)
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

	//计
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

	//猭璸衡
	int* tmp = new int[len1 + len2]{};
	for (int i = 0; i < len2; i++) {
		for (int j = 0; j < len1; j++) {
			tmp[i + j + 1] += (s1[j] - '0') * (s2[i] - '0');
		}
	}

	//矪瞶秈
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

	//临Θ﹃
	string result = {};
	for (int i = 0; i < len1 + len2; i++) {
		result = result + (char)(tmp[i] + '0');
	}
	result = clear0(result);

	//计翴
	if (dec != 0) {
		int len = result.length();
		result.insert(len - dec, ".");
	}
	if (sign) result = '-' + result;

	delete[] tmp;
	return clear0(result);
}

//﹟ゼ矪柑计场だ(ming @ 2022.04.20)
string divide(string s1, string s2)
{
	// 耞resultタ璽flag
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
	// 硈尿搭猭counter
	int counter = -1;
	// 砆埃计temp
	string s1Temp = s1;
	// 砆埃计temp    for 砆埃计埃计
	string s1TempPre = s1;
	// 砆埃计(s1), 埃计(s2)
	int s1Len = s1.size(), s2Len = s2.size();
	// result 
	string result = "";
	// ゑ耕
	if (s1Len < s2Len) // return 0
	{
		return "0";
	}
	// 猵
	else if (s1Len == s2Len)
	{
		if (sub(s1, s2)[0] == '-')
		{
			return "0";
		}
		else
		{
			// 搭瞷璽ゎ			
			while (s1Temp[0] != '-')
			{
				s1Temp = sub(s1Temp, s2);
				counter++;
			}
			// рcounter result
			char temp = counter + '0';
			result += temp;
			return result;
		}
	}
	// 砆埃计>埃计
	else
	{
		// 埃计干箂籔砆埃计
		int fill0Counter = s1.size() - s2.size();
		for (int i = 0; i < fill0Counter; i++)
		{
			s2 += "0";
		}
		// 搭砆埃计瞷璽计奔干筁箂ゎ
		while (fill0Counter >= 0)
		{
			counter = -1;
			while (s1Temp[0] != '-')
			{
				// s1TempPre0ぇ玡
				s1TempPre = s1Temp;
				s1Temp = sub(s1Temp, s2);
				counter++;
			}
			// рcounter result
			char temp = counter + '0';
			result += temp;
			// s10ぇ玡
			s1Temp = s1TempPre;
			//箂
			s2.erase(s2.end() - 1);
			fill0Counter--;
		}
		// resultタ璽腹
		if (flag == 1) // 璝璽腹碞玡'-' タ腹do nothing
		{
			result = "-" + result;
		}
		return clear0(result);
	}
}

//顶(忌秆)
string fac(string s1) {
	string result = s1;
	s1 = sub(s1, "1");
	while (s1 != "1") {
		result = multi(result, s1);
		s1 = sub(s1, "1");
	}
	return result;
}
