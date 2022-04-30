// File: BigN.h
// Creator: Yu-chen Kuo
// Last Update: 2022/04/23

//class�w�q�϶�

//2022.04.23 [�s�W] Class Integer�BDecimal

#pragma once
#include "Header.h"

//��l�ŧi
class BigN;
class Integer;
class Deciaml;

void fill100(string* s);

//�����ܼ�struct
typedef struct {
	string dataType; //�ܼƫ��A
	string name; //�ܼƦW��
	string value; //�ƭ�		//2022.4.20 [���] ���O
}Variable;

//��������struct
typedef struct {
	string name;
	string denominator;//����
	string molecular;//���l
}Farction;

//�j�ƹB��class
class BigN{
public:
	string countValue(string _in); //�p��⦡(�ǤJ�����Ǧ�) //2022.04.21 [���] �^�ǭ�
	void setVariale(string _in); //�]�w�ܼ�
	void showVariale(); //�C�L�x�s���ܼ�

	//2022.04.27 [�s�W] ���ƹB��
	string setFarction(string molecular, string denominator); //�]�w����
	Farction findFarction(string name); //�M�����
	string countFarction(string name, string op, string s2); //�p�����

private:
	string s1, s2; //�p��Ȧs
	vector<Variable> list; //�x�s�ۭq�ܼ�
	vector<Farction> farct; //�x�s����
	unsigned int farctIndex = 0; //���ƭp�ƾ�(�R�W��)
};

//�p��class
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

//���class
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


