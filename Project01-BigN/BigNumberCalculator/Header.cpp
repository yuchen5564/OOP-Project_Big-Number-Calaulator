// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/23                  

//儲存函數

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

//2022.04.21 [修復] 正負號error問題 、 ======> [待處理] * / 在首位防呆 
string infix2posfix(string _infix) {
	//2022.04.22 [新增] 輸入無空格，先分隔運算元與元素
	int len = _infix.length();
	bool f = 0;
	for (int i = 0; i < len; i++) {
		//2022.04.23 [修正] 遇到負號不會分隔
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
	stack<string> tmp; //暫存運算元
	stack<string>postfix;
	string s;
	string result = {};
	vector<string>element;
	vector<string>::iterator i;
	//先收入所有元素
	while (in >> s) {
		element.push_back(s);
	}
	int ssign = 0;//0:+ ; 1:- //紀錄正負號標記
	string snext; //儲存下一個元素
	int count = 0; //區分正負號和加減

	for (i = element.begin(); i != element.end(); i++) {
		s = *i;
		if (i != element.end() - 1) {
			snext = *(i + 1);
		}
		bool flag = 0;
		switch (sign(s)) {
		case 2: 
			//正負號處理
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
			if (s == "*" && tmp.top() == "/") { //2022.04.23 [修正] 1/3*3 = 0.99999...
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
		case 999: //非運算符號
			//處理正負號
			if (ssign == 1 && s[0] != '-')	s = '-' + s;
			else if (ssign == 1 && s[0] == '-') s.erase(0, 1);
			ssign = 0; //記錄重置
			count = 0; //記錄重置
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

//補0 --20220420更改輸入方式，使其可以處理小數對齊
void fill0(string* s1, string* s2) {
	int len1 = s1->length();
	int len2 = s2->length();
	//都沒有小數點
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

		//補齊整數位
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

		//補齊小數位
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

//已處裡小數部分(yuchen @ 2022.04.20)
//2022.04.21 [修補] 若整數位相減後為0，須補0
string clear0(string s) {
	int len = s.length();
	int count = 0;
	//處裡前方無意義0
	for (int i = 0; i < len; i++) {
		if (s[i] == '-') continue;
		if (s[i] != '0') break;
		else count++;
	}
	//if (count == len) s = "0";
	if (s[0] == '-') s.erase(1, count);
	else s.erase(0, count);

	//尋找小數點，處理後方無意義0
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
	if (s[0] == '-' && s[1] == '.') { //2022.04.21 [修補] 若整數位相減後為0，須補0
		s = '-' + s;
		s[1] = '0';
	}
	if (s[0] == '.') s = '0' + s; 
	if (s.length() == 0) s = "0"; //2022.04.21 [修補] 相減後等於0，輸出0
	return s;
}

//已處裡小數部分(yuchen @ 2022.04.20)
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

//已處裡小數部分(yuchen @ 2022.04.20)
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

	//負數處理
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

//已處裡小數部分(yuchen @ 2022.04.20)
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

	//小數
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

	//乘法計算
	int* tmp = new int[len1 + len2]{};
	for (int i = 0; i < len2; i++) {
		for (int j = 0; j < len1; j++) {
			tmp[i + j + 1] += (s1[j] - '0') * (s2[i] - '0');
		}
	}

	//處理進位
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

	//還原成字串
	string result = {};
	for (int i = 0; i < len1 + len2; i++) {
		result = result + (char)(tmp[i] + '0');
	}
	result = clear0(result);

	//小數點
	if (dec != 0) {
		int len = result.length();
		result.insert(len - dec, ".");
	}
	if (sign) result = '-' + result;

	delete[] tmp;
	return clear0(result);
}

//除法用到========================================================
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
	// 補零至整數
	for (int i = 0; i < maxDeciLen - s1DecimalLen; i++)
	{
		s1 += "0";
	}
	for (int i = 0; i < maxDeciLen - s2DecimalLen; i++)
	{
		s2 += "0";
	}

}

//每往下算一位s1就補零
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

//已處理小數部分(ming @ 2022.04.21)
string divide(string s1, string s2)
{
	// 判斷result正負的flag
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

	// 清除多餘的0
	s1 = clear0(s1);
	s2 = clear0(s2);

	// 連續減法的counter
	int counter = -1;
	// 被除數的temp
	string s1Temp = s1;
	// 上一個被除數的temp    for 被除數長度大於除數長度
	string s1TempPre = s1;
	// 被除數(s1), 除數(s2)的長度
	int s1Len = s1.size(), s2Len = s2.size();
	// result 
	string result = "";

	// 比較長度 // 直接decimal100
	if (s1Len < s2Len) result = "0." + decimal100(s1, s2);

	// 長度相同狀況
	else if (s1Len == s2Len)
	{
		// 直接decimal100
		if (sub(s1, s2)[0] == '-')  result = "0." + decimal100(s1, s2);
		else
		{
			string preS1 = s1;
			// 減到出現負為止			
			while (s1[0] != '-')
			{
				preS1 = s1;
				s1 = sub(s1, s2);
				counter++;
			}
			// 把counter 加入result
			char temp = counter + '0';
			result += temp;
			// 計算小數部分
			result += '.' + decimal100(preS1, s2); // 補小數點
		}
	}
	// 被除數長度>除數長度
	else
	{
		// 除數補零至與被除數相同 ex: 5 - 3
		int fill0Counter = s1.size() - s2.size(); // 2
		for (int i = 0; i < fill0Counter; i++)
		{
			s2 += "0";
		}
		// 減到到被除數出現負數且去掉補過的零為止
		while (fill0Counter >= 0)
		{
			counter = -1;
			while (s1Temp[0] != '-')
			{
				// 存下s1TempPre小於0之前的值
				s1TempPre = s1Temp;
				s1Temp = sub(s1Temp, s2);
				counter++;
			}
			// 把counter 加入result
			char temp = counter + '0';
			result += temp;
			// s1回到小於0之前的值
			s1Temp = s1TempPre;
			//去一個零
			if (fill0Counter > 0) s2.erase(s2.end() - 1);
			fill0Counter--;
		}
		result += "." + decimal100(s1TempPre, s2);
	}
	// result加上正負號 // 若負號就前面加'-' 正號do nothing
	if (flag == 1) result = "-" + result;
	return clear0(result);
}

//階乘(暴力解) --> TLE?快速算法?
//2022.04.21 [測試] 3000! 45s; 5000! 3min20s
string fac(string s1) {
	if (s1 == "0") return "1"; //2022.04.22 [新增] 0!定義
	string result = s1;
	s1 = sub(s1, "1");
	while (s1 != "1") {
		result = multi(result, s1);
		s1 = sub(s1, "1");
	}
	return result;
}


