// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/21

//class�w�q�϶�

#pragma once
#include "Header.h"

typedef struct {
	string dataType; //�ܼƫ��A
	string name; //�ܼƦW��
	string value; //�ƭ�		//2022.4.20 [���] ���O
}Variable;

class BigN{
public:
	//void processInput(string _in); //���R��J�⦡
	//void storeVariale(string _in); //�x�s�ܼƫ��A���
	string countValue(string _in); //�p��⦡(�ǤJ�����Ǧ�) //2022.04.21 [���] �^�ǭ�
	void setVariale(string _in); //�]�w�ܼ�

	//operator overloading
	/*string operator+(string s) { 
		string tmp = this;
		return add(tmp, s);
	}*/

	//...
	void showVariale(); //For test.

private:
	string s1, s2;
	//stack<string> number; //�x�s�Ʀr(�ȩw)
	//stack<char> sign; //�x�s�Ÿ�
	vector<Variable> list; //�x�s�ۭq�ܼ�
};

class Integer {
public:
	Integer() { value = "0"; }
	Integer(string _in) { value = _in; }

	friend Integer operator+(Integer a, Integer b){ 
		Integer tmp;
		tmp.value = add(a.value, b.value);
		return add(a.value, b.value);
	}
	string value;
};

