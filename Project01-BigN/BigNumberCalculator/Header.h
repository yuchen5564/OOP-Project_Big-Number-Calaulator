// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/17

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
// 返回: 對應優先權數字，若非運算子返回0
int sign(string _in);

// 中序式轉後序式
// 輸入: 中序式字串，每個數和符號之間要有一個空格(e.g. 1+2+3: 1 + 2 + 3)
// 返回: 後序式字串，每個數和符號之間會有一個空格(e.g. 12+3+: 1 2 + 3 +)
string infix2posfix(string _infix);

//sud、add必須同時存在(會互相呼叫)
string add(string s1, string s2);
string sub(string s1, string s2);

//補0
void fill0(string* s, int n);

//清除開頭多餘的0
string clear0(string s);