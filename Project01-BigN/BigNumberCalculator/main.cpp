// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/17

//�D�n�����ɮ�

#include "BigN.h"

int main() {
	BigN calc;
	string infix = "1 + 2 - 3";
	getline(cin, infix);
	cout << "Infix: " << infix << endl;
	cout << "Value: ";
	calc.countValue(infix);

	return 0;
}