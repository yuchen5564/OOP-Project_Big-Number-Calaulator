// File: Decimal.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/24

#include "BigN.h"


Decimal::Decimal(string _in) {
	BigN tmp;
	value = tmp.countValue(_in);
}

Decimal::Decimal(const char* _in) {
	BigN tmp;
	string s(_in);
	s = tmp.countValue(s);
	//if (s.find(".") != string::npos) fill100(&s);
	value = s;
}

Decimal& Decimal::operator=(Decimal s) {
	this->value = s.value;
	return *this;
}

Decimal& Decimal::operator=(Integer s){
	this->value = s.getValue();
	return *this;
}


Decimal Decimal::operator+(Decimal s) {
	Decimal tmp;
	tmp.value = add(this->value, s.value);
	return tmp;
}

Decimal Decimal::operator-(Decimal s) {
	Decimal tmp;
	tmp.value = sub(this->value, s.value, 1);
	return tmp;
}

Decimal Decimal::operator*(Decimal s) {
	Decimal tmp;
	tmp.value = multi(this->value, s.value);
	return tmp;
}

Decimal Decimal::operator/(Decimal s) {
	Decimal tmp;
	tmp.value = divide(this->value, s.value);
	return tmp;
}

Decimal Decimal::operator+(Integer s){
	string tmp = s.getValue();
	this->value = add(this->value, tmp);
	return *this;
}

Decimal Decimal::operator-(Integer s){
	string tmp = s.getValue();
	this->value = sub(this->value, tmp, 1);
	return *this;
}

Decimal Decimal::operator*(Integer s){
	string tmp = s.getValue();
	this->value = multi(this->value, tmp);
	return *this;
}

Decimal Decimal::operator/(Integer s){
	string tmp = s.getValue();
	this->value = divide(this->value, tmp);
	return *this;
}

Decimal operator+(Integer s, Decimal d){
	string tmp;
	tmp = add(s.getValue(), d.value);
	return Decimal(tmp);
}

Decimal operator-(Integer s, Decimal d){
	string tmp;
	//cout << d.value << endl;

	tmp = sub(s.getValue(), d.value, 1);
	//cout << tmp << endl;
	return Decimal(tmp);
}

Decimal operator*(Integer s, Decimal d){
	string tmp;
	tmp = multi(s.getValue(), d.value);
	return Decimal(tmp);
}

Decimal operator/(Integer s, Decimal d){
	string tmp;
	tmp = divide(s.getValue(), d.value);
	return Decimal(tmp);
}

istream& operator>>(istream& input, Decimal& s) {
	string tmp;
	input >> tmp;
	s.value = tmp;
	return input;
}

/*ostream& operator<<(ostream& output, const Decimal& a) {
	string tmp = a.value;
	if (a.value.find(".") != string::npos) fill100(&tmp);
	output << tmp;
	return output;
}*/