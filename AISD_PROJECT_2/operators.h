
#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include "node.h"
#include "string.h"
#include "CONTAINERS_CONSTS.h"

std::ostream& operator<<(std::ostream& out, const Node<int>& s) {
	out << s.getVal();
	return out;
}
std::ostream& operator<<(std::ostream& out, const Node<String>& s) {
	out << s.getVal().getVal();
	return out;
}
std::ostream& operator<<(std::ostream& out, const String& s) {
	out << s.getVal();
	return out;
}
std::istream& operator>>(std::istream& is, String& s) {
	if (s.bufs != 1) {
		s.cleanVal();
		s.val = new char[stringBuf];
		s.bufs = 1;
	}
	s.size = 0;
	int ch = EOF;
	while (ch) {
		ch = getchar();
		if (ch == '\n' || ch == ' ')
			ch = 0;
		else if (ch == EOF) {
			ch = 0;
			String::EOFdetected = 1;
		}

		if (s.size < stringBuf * s.bufs)
			s.val[s.size++] = ch;
		else {
			s.bufs++;
			s.addMemory(s.bufs * stringBuf);
			s.val[s.size++] = ch;
		}
	}

	return is;
}
#endif