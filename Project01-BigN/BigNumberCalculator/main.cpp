// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/27

//�D�n�����ɮ�

//2022.04.21 [�s�W] �i�]�w�ܼƶi��p��
//2022.04.25 [�ק�] ��X�榡(�|�M������)
//2022.04.27 [�ק�] Error code �榡

#include "BigN.h"

#define CLS		//����M������
//#define OVERLOADING	//����overloading

//2022.04.27 [�s�W] ASCII�Ϯ�
void bigN() {
	//SET_COLOR(14);
	cout << " ______    _         ____  _____  \n" <<
		"|_   _ \\  (_)       |_   \\|_   _| \n" <<
		"  | |_) | __   .--./) |   \\ | |   \n" <<
		"  |  __'.[  | / /'`\\; | |\\ \\| |   \n" <<
		" _| |__) || | \\ \\._//_| |_\\   |_  \n" <<
		"|_______/[___].',__`|_____|\\____| \n" <<
		"             ( ( __))             \n";
	//SET_COLOR(15);
}

int main() {
	
	SetConsoleTitleA("[OOP] Project01 - Big Number Calculator");
	bigN();

#ifdef OVERLOADING
	cout << "\n===Test operator overloading===\n";
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
#endif // OVERLOADING

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
			bigN();
			cout << INPUT;
			continue;
		}

		if (input == "exit") { //2022.04.27 [�s�W] exit
			
			system("cls");
			//bigN();

			SET_COLOR(10);
			cout << "\n  ~~~Goodbye!~~~\n";
			SET_COLOR(15);

			return 0;
		}

		if (input == "memory") { //2022.04.25 [�s�W] �d���ܼ�
			calc.showVariale();
			cout << "\n-------------------------------\n";
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
			
			//cout << "[Error] Input cannot be blank!\n";

			ERROR("Input cannot be blank!");
			cout<<"\n-------------------------------\n" INPUT;
			
			continue;
		}

		stringstream in(input);
		in >> tmp;

		//2022.04.21 [���] �P�O�覡
		//2022.04.26 [�ץ�] �P�O�覡
		if (tmp == "Set" && input.find("=") != string::npos) {  //Set Integer/Decimal
			calc.setVariale(input);
			//calc.showVariale();
		}
		else if (input.find("=") != string::npos && input.find("=")!=input.length()-1) { //A = A + 3
			calc.setVariale(input);
			//calc.showVariale();
		}
		else { // 10+10
			tmp = calc.countValue(input);
			if (tmp != "Error") cout << "> Value: " << tmp << "\n";
		}
		cout << "\n-------------------------------\n";

		cout << INPUT;
	}

	return 0;
}