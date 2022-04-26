// File: Header.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

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
// ��^: �����u���v�Ʀr�A�Y�D�B��l��^999
int sign(string _in);

// ���Ǧ����Ǧ�
// ��J: ���Ǧ��r��A�C�ӼƩM�Ÿ������n���@�ӪŮ�(e.g. 1+2+3: 1 + 2 + 3)
// ��^: ��Ǧ��r��A�C�ӼƩM�Ÿ������|���@�ӪŮ�(e.g. 12+3+: 1 2 + 3 +)
string infix2posfix(string _infix);

//sud�Badd�����P�ɦs�b(�|���۩I�s)
string add(string s1, string s2);
string sub(string s1, string s2, int f);

string multi(string s1, string s2);
string divide(string s1, string s2); //By ming. 

//����(�ɤO��)
string fac(string s1);

//��0  --20220420����J�覡�A�Ϩ�i�H�B�̤p�ƹ��
void fill0(string* s1, string* s2);

//�M���}�Y�h�l��0
string clear0(string s);

//�ˬd�p�G���O�Oint�A�h���p���I��Ҧ��줸	//2022.04.23 Add
void checkInteger(string* s);


//���k��==========================================
void dec2int(string& s1, string& s2);

//�C���U��@��s1�N�ɹs
string decimal100(string s1, string s2);
string power(string s1, string s2);
