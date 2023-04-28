
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
#endif