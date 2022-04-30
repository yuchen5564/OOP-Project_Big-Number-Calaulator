// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/23

//class定義區塊

//2022.04.23 [新增] Class Integer、Decimal

#pragma once
#include "Header.h"

//初始宣告
class BigN;
class Integer;
class Deciaml;

void fill100(string* s);

//紀錄變數struct
typedef struct {
	string dataType; //變數型態
	string name; //變數名稱
	string value; //數值		//2022.4.20 [更改] 型別
}Variable;

//紀錄分數struct
typedef struct {
	string name;
	string denominator;//分母
	string molecular;//分子
}Farction;

//大數運算class
class BigN{
public:
	string countValue(string _in); //計算算式(傳入為中序式) //2022.04.21 [更改] 回傳值
	void setVariale(string _in); //設定變數
	void showVariale(); //列印儲存的變數

	//2022.04.27 [新增] 分數運算
	string setFarction(string molecular, string denominator); //設定分數
	Farction findFarction(string name); //尋找分數
	string countFarction(string name, string op, string s2); //計算分數

private:
	string s1, s2; //計算暫存
	vector<Variable> list; //儲存自訂變數
	vector<Farction> farct; //儲存分數
	unsigned int farctIndex = 0; //分數計數器(命名用)
};

//小數class
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

//整數class
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
};


