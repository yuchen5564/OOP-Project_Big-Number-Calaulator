// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/27

//�D�n�����ɮ�

//2022.04.21 [�s�W] �i�]�w�ܼƶi��p��
//2022.04.25 [�ק�] ��X�榡(�|�M������)
//2022.04.27 [�ק�] Error code �榡

#include "BigN.h"



//�}�Y�Ϯ�
//2022.04.27 [�s�W] ASCII�Ϯ�
void bigN() {
	cout << " ______    _         ____  _____  \n" <<
		"|_   _ \\  (_)       |_   \\|_   _| \n" <<
		"  | |_) | __   .--./) |   \\ | |   \n" <<
		"  |  __'.[  | / /'`\\; | |\\ \\| |   \n" <<
		" _| |__) || | \\ \\._//_| |_\\   |_  \n" <<
		"|_______/[___].',__`|_____|\\____| \n" <<
		"             ( ( __))             \n";
}

int main() {
	
	//console�]�w
	SetConsoleTitleA("[OOP] Project01 - Big Number Calculator");
	bigN();

	//����operator overloading
#ifdef OVERLOADING
	cout << "\n===Test operator overloading===\n";
	string num1 = "10.5", num2 = "45.65";
	Integer i1 = num1, i2 = num2;
	Decimal d1 = num1, d2 = num2;
	cout << "\n[Number]\nnum1 = " << num1 << "\nnum2 = " << num2 << endl;
	cout << "\n[Integer]\ni1 = " << i1 << "\ni2 = " << i2 << endl;
	cout << "\n[Decimal]\nd1 = " << d1 << "\nd2 = " << d2 << endl;

	cout << "\n[Integer & Integer]\n";
	cout << "i1+i2 = " << i1 + i2 << endl;
	cout << "i1-i2 = " << i1 - i2 << endl;
	cout << "i1*i2 = " << i1 * i2 << endl;
	cout << "i1/i2 = " << i1 / i2 << endl;

	cout << "\n[Integer & Decimal]\n";
	cout << "i1+d2 = " << i1 + d2 << endl;
	cout << "i1-d2 = " << i1 - d2 << endl;
	cout << "i1*d2 = " << i1 * d2 << endl;
	cout << "i1/d2 = " << i1 / d2 << endl;

	cout << "\n[Decimal & Integer]\n"; //�p�Ʀ��
	cout << "d1+i2 = " << d1 + i2 << endl;
	cout << "d1-i2 = " << d1 - i2 << endl;
	cout << "d1*i2 = " << d1 * i2 << endl;
	cout << "d1/i2 = " << d1 / i2 << endl;

	cout << "\n[Decimal & Decimal]\n"; //�p�Ʀ��
	cout << "d1+d2 = " << d1 + d2 << endl;
	cout << "d1-d2 = " << d1 - d2 << endl;
	cout << "d1*d2 = " << d1 * d2 << endl;
	cout << "d1/d2 = " << d1 / d2 << endl;

	cout << "\n===============================\n";
#endif // OVERLOADING

#ifdef CALCULATOR
	BigN calc; //�j�ƭp��class
	string input = "1 + 2 - 3"; //�x�s��J���
	string tmp; //�Ȧs���

	//������J
	cout << INPUT;
	while (getline(cin, input)) {

		//�M������
#ifdef CLS
		system("cls");
#endif // CLS	

		cout << "-------------------------------\n\n";
		cout << "> Your input : " << input << "\n\n";

		//��Jcls�A�M������
		if (input == "cls") {	//2022.04.25 [�s�W] �M������
			system("cls");
			bigN();
			cout << INPUT;
			continue;
		}

		//��Jexit�A�����{��
		if (input == "exit") { //2022.04.27 [�s�W] exit

			system("cls");

			SET_COLOR(10);
			cout << "\n  ~~~Goodbye!~~~\n";
			SET_COLOR(15);

			return 0;
		}

		//��Jmemory�A�d�ݤw�]�w���ܼ�
		if (input == "memory") { //2022.04.25 [�s�W] �d���ܼ�
			calc.showVariale();
			cout << "\n-------------------------------\n";
			cout << INPUT;
			continue;
		}

		//�ˬd��J�O�_�O�ť�
		bool flag = 0;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] != ' ') {
				flag = 1;
				break;
			}
		}

		//��J���ťաA��Xerror�A�������
		if (input == "" || !flag) {

			ERROR("Input cannot be blank!");
			cout << "\n-------------------------------\n" INPUT;
			continue;
		}

		//�}�l���R�⦡========================================================================
		stringstream in(input);
		in >> tmp;

		//Input: Set Integer/Decimal A = 10.4
		//2022.04.21 [���] �P�O�覡
		//2022.04.26 [�ץ�] �P�O�覡
		if (tmp == "Set" && input.find("=") != string::npos) {  //Set Integer/Decimal
			calc.setVariale(input);
		}
		//Input: A = A + B
		else if (input.find("=") != string::npos && input.find("=") != input.length() - 1) { //A = A + 3
			calc.setVariale(input);
		}
		//Input: �@��|�h�B��
		else {
			tmp = calc.countValue(input);
			//�^�ǭȤ���Error�A��X���G
			if (tmp != "Error") cout << "> Value: " << tmp << "\n";
		}
		cout << "\n-------------------------------\n";

		//���ݱ����U�@����J
		cout << INPUT;
	}
#endif // CALCULATOR

	

	return 0;
}