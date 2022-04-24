// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/23

//class�w�q�϶�

//2022.04.23 [�s�W] Class Integer�BDecimal

#pragma once
#include "Header.h"

class BigN;
class Integer;
class Deciaml;

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


