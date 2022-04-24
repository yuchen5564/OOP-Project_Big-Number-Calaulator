// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/23

//class定義區塊

//2022.04.23 [新增] Class Integer、Decimal

#pragma once
#include "Header.h"

class BigN;
class Integer;
class Deciaml;

typedef struct {
	string dataType; //變數型態
	string name; //變數名稱
	string value; //數值		//2022.4.20 [更改] 型別
}Variable;

class BigN{
public:
	//void processInput(string _in); //分析輸入算式
	//void storeVariale(string _in); //儲存變數型態資料
	string countValue(string _in); //計算算式(傳入為中序式) //2022.04.21 [更改] 回傳值
	void setVariale(string _in); //設定變數

	//operator overloading
	/*string operator+(string s) { 
		string tmp = this;
		return add(tmp, s);
	}*/

	//...
	void showVariale(); //For test.

private:
	string s1, s2;
	//stack<string> number; //儲存數字(暫定)
	//stack<char> sign; //儲存符號
	vector<Variable> list; //儲存自訂變數
};

class Decimal {
public:
	Decimal() { value = "0.0"; }
	Decimal(string _in);
	Decimal(const char* _in);

	string getValue() { return this->value; }

	Decimal& operator=(Decimal s);
	Decimal& operator=(Integer s);

	//Decimal & Decimal
	Decimal operator+(Decimal s);
	Decimal operator-(Decimal s);
	Decimal operator*(Decimal s);
	Decimal operator/(Decimal s);

	//Decimal & Integer
	Decimal operator+(Integer s);
	Decimal operator-(Integer s);
	Decimal operator*(Integer s);
	Decimal operator/(Integer s);

	//Integer & Decimal
	friend Decimal operator+(Integer s, Decimal d);
	friend Decimal operator-(Integer s, Decimal d);
	friend Decimal operator*(Integer s, Decimal d);
	friend Decimal operator/(Integer s, Decimal d);


	friend istream& operator>>(istream& input, Decimal& s);
	friend ostream& operator<<(ostream& output, const Decimal& a);


private:
	string value;
};

class Integer {
public:
	Integer() { value = "0"; }
	Integer(string _in);
	Integer(const char* _in);

	string getValue() { return this->value; }

	Integer& operator=(Integer s);
	Integer& operator=(Decimal d);

	//Integer & Integer
	Integer operator+(Integer s);
	Integer operator-(Integer s);
	Integer operator*(Integer s);
	Integer operator/(Integer s);

	friend istream& operator>>(istream& input, Integer& s);
	friend ostream& operator<<(ostream& output, const Integer& a);


private:
	string value;
	//	int a;
};


