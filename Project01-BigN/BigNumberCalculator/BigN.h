// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/15

//class定義區塊

#pragma once
#include "Header.h"

typedef struct {
	string dataType; //變數型態
	string name; //變數名稱
	int value; //數值	
}Variable;

class BigN{
public:
	void processInput(string _in); //分析輸入算式
	void storeVariale(string _in); //儲存變數型態資料
	//...

private:
	stack<string> number; //儲存數字(暫定)
	stack<char> sign; //儲存符號
	vector<Variable> list; //儲存自訂變數
};

