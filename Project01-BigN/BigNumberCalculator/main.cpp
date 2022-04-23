// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

//主要執行檔案

//2022.04.21 [新增] 可設定變數進行計算

#include "BigN.h"
#include <Windows.h>

int main() {
	//string test(300000, '0');
	//cout << test << endl;
	SetConsoleTitleA("Big Number Calculator");

	BigN calc;
	string input = "1 + 2 - 3";
	string tmp;
	cout << "Input: ";
	while (getline(cin, input)) {
		bool flag = 0;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] != ' ') {
				flag = 1;
				break;
			}
		}
		if(input == "" || !flag) {
			cout << "[Error] Input cannot be blank!\nInput: ";
			continue;
		}
		//cout << input.length() << endl;
		stringstream in(input);
		in >> tmp;
		//if () {
		if(tmp == "Set" && input.find("=") != string::npos){ //2022.04.21 [更改] 判別方式
			calc.setVariale(input);
			calc.showVariale();
		}
		else {
			//cout << "Infix: " << input << endl;
			//cout << "Postfix: " << infix2posfix(input) << endl;
			//cout << "Value: ";
			tmp = calc.countValue(input);
			if (tmp != "Error") cout << "Value: " << tmp << endl;
		}
		cout << "Input: ";
	}
	
	return 0;
}