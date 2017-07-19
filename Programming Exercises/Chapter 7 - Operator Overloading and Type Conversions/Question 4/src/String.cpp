/*
 * String.cpp
 * Author: suyashd95
 */

#include "String.h"

#include <cstring>

String::String() {

	length = 0;
	str = new char[length + 1];
//	std::cout << "Default constructor called." << std::endl;
}

String::String(const char* str) {

	this->length = strlen(str);
	this->str = new char[this->length + 1];
	strcpy(this->str, str);
//	std::cout << "Parameterized constructor called." << std::endl;
}

String::String(const String& s) {

	this->length = s.length;
	this->str = new char[this->length + 1];
	strcpy(this->str, s.str);
//	std::cout << "Copy Constructor called." << std::endl;
}

String& String::operator =(const String& rhs) {

	this->length = rhs.length;
	delete [] this->str;

	this->str = new char[this->length + 1];
	strcpy(this->str, rhs.str);
//	std::cout << " Copy Assignment Operator called." << std::endl;

	return *this;
}

String::~String() {

	delete [] str;
//	std::cout << "Destructor called." << std::endl;
}
