
#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include "node.h"

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
//ostream& operator<<(ostream& out, const Pair<String,int>& s)
#endif