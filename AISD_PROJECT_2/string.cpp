#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "CONTAINERS_CONSTS.h"
#include "Move.h"
#include "String.h"
#include <iostream>

bool String::EOFdetected = 0;
String::String() {
	val = nullptr;
	size = 0;
	bufs = 0;
}
char* String::getVal() const {
	return this->val;
}
bool String::isEmpty() {
	if (this->size == 0 || this->size == 1)
		return true;
	return false;
}
void String::addMemory(int newSize) {
	char* buf = Move<char*>(val);
	val = new char[newSize];

	//przepisuje tablice
	for (int i = 0; i < size && i < newSize; i++)
		val[i] = buf[i];
	val[newSize - 1] = '\0';

	if (size == 0 && newSize > 0) {
		size++;
		val[0] = '\0';
	}

	if (buf != nullptr)
		delete[] buf;
}
bool String::getEOFdetection() {
	return String::EOFdetected;
}
void String::getline() {
	if (bufs != 1) {
		cleanVal();
		this->val = new char[stringBuf];
		bufs = 1;
	}
	size = 0;
	int ch = EOF;
	while (ch) {
		ch = getchar();
		if (ch == '\n')
			ch = 0;
		else if (ch == EOF) {
			ch = 0;
			String::EOFdetected = 1;
		}

		if (size < stringBuf * bufs)
			val[size++] = ch;
		else {
			bufs++;
			addMemory(bufs * stringBuf);
			val[size++] = ch;
		}
	}
}
void String::cleanVal() {
	if (this->val != nullptr) {
		delete[] this->val;
		this->val = nullptr;
	}
}
int String::find(char c, int start) const {
	char* pos = strchr(val + start, c);
	if (pos == NULL)
		return -1;
	else
		return int(pos - val);
}
void String::erase(int start, int n) {
	if (n == 0)
		return;
	int id = start;
	for (int i = start; i+n < this->size; i++) {
		val[i] = val[i + n];
	}
	size -= n;

	if (size <= 0) {
		size = 0;
		bufs = 0;
		cleanVal();
	}
	else {
		int oldBufs = bufs;
		while (stringBuf * bufs >= size)
			bufs--;
		bufs++;
		if (oldBufs != bufs) {
			char* buf = Move<char*>(val);

			val = new char[bufs * stringBuf];
			strcpy(val, buf);
			delete[] buf;
		}
	}
}
int String::getSize() const {
	return this->size;
}
String::String(const String& other) {
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = other;
}
String::String(String&& other) {
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = Move<String>(other);
}
String::String(const char*&& other) {
	this->size = 0;
	this->val = nullptr;
	this->bufs = 0;
	*this = other;
}
char& String::operator[](int i) {
	return this->val[i];
}
void String::clear() {
	if (bufs != 1) {
		delete[] this->val;
		this->val = new char[stringBuf];
		bufs = 1;
	}
	size = 1;
	val[0]='\0';
}
String& String::operator=(const char* s) {
	if (s == nullptr) {
		cleanVal();
		size = 0;
		bufs = 0;
		return *this;
	}
	int i = 0;
	size_t s_size = strlen(s) + 1;		// +1 cuz of '\0' at the end
	if (s_size > bufs * stringBuf) {
		while (bufs * stringBuf < s_size)
			bufs++;
		cleanVal();
		this->val = new char[bufs*stringBuf];
	}
	strcpy(val, s);
	this->val[s_size - 1] = 0;
	this->size = s_size;
	return *this;
}
void String::getword() {
	if (this->bufs != 1) {
		this->cleanVal();
		this->val = new char[stringBuf];
		this->bufs = 1;
	}
	this->size = 0;
	int ch = EOF;
	while (ch) {
		ch = getchar();
		if (ch == '\n' || ch == ' ')
			ch = 0;
		else if (ch == EOF) {
			ch = 0;
			String::EOFdetected = 1;
		}

		if (this->size < stringBuf * this->bufs)
			this->val[this->size++] = ch;
		else {
			this->bufs++;
			this->addMemory(this->bufs * stringBuf);
			this->val[this->size++] = ch;
		}
	}
}
String& String::operator=(const String& s) {
	if (this == &s)
		return *this;

	if (s.bufs != this->bufs) {
		cleanVal();
		this->val = new char[s.bufs * stringBuf];
		this->bufs = s.bufs;
	}
	this->size = s.size;

	strcpy(val, s.val);
	return *this;
}
String& String::operator=(char*&& s) {
	if (s == nullptr) {
		cleanVal();
		size = 0;
		bufs = 0;
		return *this;
	}
	std::swap(this->val, s);
	int i = 0;
	while (val[i] != 0)
	{
		size++;
		i++;
	}
	size++;
	return *this;
}
String& String::operator=(String&& s) {
	this->size = s.size;
	this->bufs = s.bufs;
	std::swap(this->val, s.val);
	s.size = 0;
	s.bufs = 0;
	s.val = nullptr;
	return *this;
}
const bool String::operator==(const String& s) const{
	if (s.val == nullptr && this->val == nullptr)
		return true;
	if (size != s.size || s.val == nullptr)
		return false;
	for (int i = 0; i < size; i++) {
		if (val[i] != s.val[i])
			return false;
	}
	return true;
}
const bool String::operator!=(const String& s) const{
	return !(*this == s);
}
const bool String::operator==(const char* s) const {
	if (s == nullptr && this->val == nullptr)
		return true;
	if (s == nullptr)
		return false;
	int i = 0;
	while (s[i] != '\0' && i < this->size) {
		if (s[i] != val[i])
			return false;
		i++;
	}
	if (this->size > i+1)
		return false;
	return true;
}
const bool String::operator!=(const char* s) const {
	return !(*this == s);
}
String& String::operator+=(const char s) {
	if (this->size + 1 > stringBuf * bufs)
		addMemory(stringBuf * (++bufs));
	this->size++;
	val[size - 2] = s;
	val[size - 1] = 0;
	return *this;
}

String::~String() {
	if (this != nullptr && val != nullptr)
		delete[] val;
}


String operator+(const char c, const String& s) {
	String result;
	result.val = new char[s.size + 1];
	result.val[0] = c;
	result.size = s.size + 1;

	for (int i = 1; i < result.size; i++)
		result.val[i] = s.val[i - 1];
	return result;
}