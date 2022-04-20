// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/20

//class�w�q�϶�

#pragma once
#include "Header.h"

typedef struct {
	string dataType; //�ܼƫ��A
	string name; //�ܼƦW��
	string value; //�ƭ�		//2022.4.20 ��﫬�O
}Variable;

class BigN{
public:
	//void processInput(string _in); //���R��J�⦡
	//void storeVariale(string _in); //�x�s�ܼƫ��A���
	void countValue(string _in); //�p��⦡(�ǤJ�����Ǧ�)
	void setVariale(string _in); //�]�w�ܼ�
	//...
	void showVariale(); //For test.

private:
	//stack<string> number; //�x�s�Ʀr(�ȩw)
	//stack<char> sign; //�x�s�Ÿ�
	vector<Variable> list; //�x�s�ۭq�ܼ�
};

