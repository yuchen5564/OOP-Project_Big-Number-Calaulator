// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/17

//��m�һݪ����Y�ɮ׻P������
//main.cpp�ФŤޤJ

#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

// �B��l�u���v
// ��J: �ƭȦr��ιB��l�r��
// ��^: �����u���v�Ʀr�A�Y�D�B��l��^0
int sign(string _in);

// ���Ǧ����Ǧ�
// ��J: ���Ǧ��r��A�C�ӼƩM�Ÿ������n���@�ӪŮ�(e.g. 1+2+3: 1 + 2 + 3)
// ��^: ��Ǧ��r��A�C�ӼƩM�Ÿ������|���@�ӪŮ�(e.g. 12+3+: 1 2 + 3 +)
string infix2posfix(string _infix);

//sud�Badd�����P�ɦs�b(�|���۩I�s)
string add(string s1, string s2);
string sub(string s1, string s2);

//��0
void fill0(string* s, int n);

//�M���}�Y�h�l��0
string clear0(string s);