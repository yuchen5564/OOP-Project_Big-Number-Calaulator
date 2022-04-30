// File: main.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/27

//主要執行檔案

//2022.04.21 [新增] 可設定變數進行計算
//2022.04.25 [修改] 輸出格式(會清除版面)
//2022.04.27 [修改] Error code 格式

#include "BigN.h"



//開頭圖案
//2022.04.27 [新增] ASCII圖案
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
	
	//console設定
	SetConsoleTitleA("[OOP] Project01 - Big Number Calculator");
	bigN();

	//測試operator overloading
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

	cout << "\n[Decimal & Integer]\n"; //小數位數
	cout << "d1+i2 = " << d1 + i2 << endl;
	cout << "d1-i2 = " << d1 - i2 << endl;
	cout << "d1*i2 = " << d1 * i2 << endl;
	cout << "d1/i2 = " << d1 / i2 << endl;

	cout << "\n[Decimal & Decimal]\n"; //小數位數
	cout << "d1+d2 = " << d1 + d2 << endl;
	cout << "d1-d2 = " << d1 - d2 << endl;
	cout << "d1*d2 = " << d1 * d2 << endl;
	cout << "d1/d2 = " << d1 / d2 << endl;

	cout << "\n===============================\n";
#endif // OVERLOADING

#ifdef CALCULATOR
	BigN calc; //大數計算class
	string input = "1 + 2 - 3"; //儲存輸入資料
	string tmp; //暫存資料

	//接收輸入
	cout << INPUT;
	while (getline(cin, input)) {

		//清除版面
#ifdef CLS
		system("cls");
#endif // CLS	

		cout << "-------------------------------\n\n";
		cout << "> Your input : " << input << "\n\n";

		//輸入cls，清除版面
		if (input == "cls") {	//2022.04.25 [新增] 清除版面
			system("cls");
			bigN();
			cout << INPUT;
			continue;
		}

		//輸入exit，結束程式
		if (input == "exit") { //2022.04.27 [新增] exit

			system("cls");

			SET_COLOR(10);
			cout << "\n  ~~~Goodbye!~~~\n";
			SET_COLOR(15);

			return 0;
		}

		//輸入memory，查看已設定的變數
		if (input == "memory") { //2022.04.25 [新增] 查看變數
			calc.showVariale();
			cout << "\n-------------------------------\n";
			cout << INPUT;
			continue;
		}

		//檢查輸入是否是空白
		bool flag = 0;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] != ' ') {
				flag = 1;
				break;
			}
		}

		//輸入為空白，輸出error，停止執行
		if (input == "" || !flag) {

			ERROR("Input cannot be blank!");
			cout << "\n-------------------------------\n" INPUT;
			continue;
		}

		//開始分析算式========================================================================
		stringstream in(input);
		in >> tmp;

		//Input: Set Integer/Decimal A = 10.4
		//2022.04.21 [更改] 判別方式
		//2022.04.26 [修正] 判別方式
		if (tmp == "Set" && input.find("=") != string::npos) {  //Set Integer/Decimal
			calc.setVariale(input);
		}
		//Input: A = A + B
		else if (input.find("=") != string::npos && input.find("=") != input.length() - 1) { //A = A + 3
			calc.setVariale(input);
		}
		//Input: 一般四則運算
		else {
			tmp = calc.countValue(input);
			//回傳值不為Error，輸出結果
			if (tmp != "Error") cout << "> Value: " << tmp << "\n";
		}
		cout << "\n-------------------------------\n";

		//等待接收下一次輸入
		cout << INPUT;
	}
#endif // CALCULATOR

	

	return 0;
}