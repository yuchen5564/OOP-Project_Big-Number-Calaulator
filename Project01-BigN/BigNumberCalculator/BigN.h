// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/15

//class�w�q�϶�

#pragma once
#include "Header.h"

typedef struct {
	string dataType; //�ܼƫ��A
	string name; //�ܼƦW��
	int value; //�ƭ�	
}Variable;

class BigN{
public:
	void processInput(string _in); //���R��J�⦡
	void storeVariale(string _in); //�x�s�ܼƫ��A���
	//...

private:
	stack<string> number; //�x�s�Ʀr(�ȩw)
	stack<char> sign; //�x�s�Ÿ�
	vector<Variable> list; //�x�s�ۭq�ܼ�
};

