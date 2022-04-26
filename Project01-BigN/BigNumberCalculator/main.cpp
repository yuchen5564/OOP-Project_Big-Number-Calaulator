// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/25

//�D�n�����ɮ�

//2022.04.21 [�s�W] �i�]�w�ܼƶi��p��
//2022.04.25 [�ק�] ��X�榡(�|�M������)

#include "BigN.h"
#include <Windows.h>
#define INPUT "\n[Input] "

#define CLS		//����M������
//#define OVERLOADING	//����overloading


int main() {
	SetConsoleTitleA("[OOP Project01] Big Number Calculator");

#ifdef OVERLOADING
	cout << "===Test operator overloading===\n";
	cout << "[Decimal]\n";
	Decimal a = "301.987-1", b = "3", c;
	Integer d, e = "123", f = "123";
	d = a + b;
	c = e + a;
	cout << c << endl;
	cout << d << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "a+b = " << a + b << endl;
	cout << "a-b = " << a - b << endl;
	cout << "a*b = " << a * b << endl;
	cout << "a/b = " << a / b << endl;
	cout << "===============================\n";
#endif // TEST_OVERLOADING

	BigN calc;
	string input = "1 + 2 - 3";
	string tmp;
	cout << INPUT;
	while (getline(cin, input)) {

		//�O�_�n�M������
#ifdef CLS
		system("cls");
#endif // RELEASE

		cout << "-------------------------------\n\n";
		cout << "> Your input : " << input << "\n\n";
		if (input == "cls") {	//2022.04.25 [�s�W] �M������
			system("cls");
			cout << INPUT;
			continue;
		}

		if (input == "memory") { //2022.04.25 [�s�W] �d���ܼ�
			calc.showVariale();
			cout << INPUT;
			continue;
		}

		bool flag = 0;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] != ' ') {
				flag = 1;
				break;
			}
		}

		if (input == "" || !flag) {
			cout << "[Error] Input cannot be blank!\n" INPUT;
			continue;
		}

		stringstream in(input);
		in >> tmp;

		if (tmp == "Set" && input.find("=") != string::npos) { //2022.04.21 [���] �P�O�覡
			calc.setVariale(input);
			calc.showVariale();
		}
		else {
			tmp = calc.countValue(input);
			if (tmp != "Error") cout << "> Value: " << tmp << "\n";
		}
		cout << "\n-------------------------------\n";

		cout << INPUT;
	}

	return 0;
}