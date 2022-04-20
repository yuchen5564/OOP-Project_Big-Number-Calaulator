// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/17

//主要執行檔案

#include "BigN.h"
#include <Windows.h>


int main() {
	SetConsoleTitleA("Big Number Calculator");

	BigN calc;
	string infix = "1 + 2 - 3";

	
	do {
		if (infix == "") cout << "[Error] Input cannot be blank!\n";
		cout << "Input: ";
		getline(cin, infix);
	} while (infix == "");
	
	cout << "Infix: " << infix << endl;
	cout << "Postfix: " << infix2posfix(infix) << endl;
	cout << "Value: ";
	calc.countValue(infix);

	return 0;
}