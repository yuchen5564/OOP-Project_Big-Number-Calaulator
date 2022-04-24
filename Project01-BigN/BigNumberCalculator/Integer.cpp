// File: Integer.cpp
// Creator: Yu-chen Kuo
// Last Update: 2022/04/23

#include "BigN.h"

Integer::Integer(string _in) {
	BigN tmp;
	value =  tmp.countValue(_in);
	checkInteger(&value);
}

Integer::Integer(const char* _in) {
	BigN tmp;
	string s(_in);
	s = tmp.countValue(s);
	checkInteger(&s);
	value = s;
}

Integer& Integer::operator=(Integer s) {
	checkInteger(&s.value);
	this->value = s.value;
	return *this;
}

Integer& Integer::operator=(Decimal d) {
	string tmp = d.getValue();
	checkInteger(&tmp);
	this->value = tmp;
	return *this;

}

Integer Integer::operator+(Integer s) {
	Integer tmp;
	tmp.value = add(this->value, s.value);
	return tmp;
}

Integer Integer::operator-(Integer s) {
	Integer tmp;
	tmp.value = sub(this->value, s.value);
	return tmp;
}

Integer Integer::operator*(Integer s) {
	Integer tmp;
	tmp.value = multi(this->value, s.value);
	return tmp;
}

Integer Integer::operator/(Integer s) {
	Integer tmp;
	tmp.value = divide(this->value, s.value);
	return tmp;
}

istream& operator>>(istream& input, Integer& s) {
	string tmp;
	input >> tmp;
	checkInteger(&tmp);
	s.value = tmp;
	return input;
}

ostream& operator<<(ostream& output, const Integer& a) {
	output << a.value;
	return output;
}