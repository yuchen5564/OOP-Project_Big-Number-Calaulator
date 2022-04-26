// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

//放置所需的標頭檔案與全域函數
//main.cpp請勿引入

#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

// 運算子優先權
// 輸入: 數值字串或運算子字串
// 返回: 對應優先權數字，若非運算子返回999
int sign(string _in);

// 中序式轉後序式
// 輸入: 中序式字串，每個數和符號之間要有一個空格(e.g. 1+2+3: 1 + 2 + 3)
// 返回: 後序式字串，每個數和符號之間會有一個空格(e.g. 12+3+: 1 2 + 3 +)
string infix2posfix(string _infix);

//sud、add必須同時存在(會互相呼叫)
string add(string s1, string s2);
string sub(string s1, string s2, int f);

string multi(string s1, string s2);
string divide(string s1, string s2); //By ming. 

//階乘(暴力解)
string fac(string s1);

//補0  --20220420更改輸入方式，使其可以處裡小數對齊
void fill0(string* s1, string* s2);

//清除開頭多餘的0
string clear0(string s);

//檢查如果型別是int，去除小數點後所有位元	//2022.04.23 Add
void checkInteger(string* s);


//除法用==========================================
void dec2int(string& s1, string& s2);

//每往下算一位s1就補零
string decimal100(string s1, string s2);
string power(string s1, string s2);
