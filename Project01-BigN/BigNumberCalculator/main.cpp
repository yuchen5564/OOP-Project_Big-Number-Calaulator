// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/25

//主要執行檔案

//2022.04.21 [新增] 可設定變數進行計算
//2022.04.25 [修改] 輸出格式(會清除版面)

#include "BigN.h"
#include <Windows.h>
#define INPUT "\n[Input] "

#define CLS		//控制清除版面
//#define OVERLOADING	//測試overloading


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

		//是否要清除版面
#ifdef CLS
		system("cls");
#endif // RELEASE

		cout << "-------------------------------\n\n";
		cout << "> Your input : " << input << "\n\n";
		if (input == "cls") {	//2022.04.25 [新增] 清除版面
			system("cls");
			cout << INPUT;
			continue;
		}

		if (input == "memory") { //2022.04.25 [新增] 查看變數
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

		if (tmp == "Set" && input.find("=") != string::npos) { //2022.04.21 [更改] 判別方式
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