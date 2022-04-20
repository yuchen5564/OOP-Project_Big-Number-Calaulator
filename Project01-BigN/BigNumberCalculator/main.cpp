// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

//�D�n�����ɮ�

//2022.04.21 [�s�W] �i�]�w�ܼƶi��p��(�|���B�� A = A + 2)

#include "BigN.h"
#include <Windows.h>

int main() {
	SetConsoleTitleA("Big Number Calculator");

	BigN calc;
	string input = "1 + 2 - 3";
	string tmp;
	cout << "Input: ";
	while (getline(cin, input)) {
		while (input == "") {
			cout << "[Error] Input cannot be blank!\nInput: ";
			getline(cin, input);
		}
		stringstream in(input);
		in >> tmp;
		if (tmp == "Set") {
			calc.setVariale(input);
			//calc.showVariale();
		}
		else {
			//cout << "Infix: " << input << endl;
			//cout << "Postfix: " << infix2posfix(input) << endl;
			//cout << "Value: ";
			calc.countValue(input);
		}
		cout << "Input: ";
	}
	
	return 0;
}