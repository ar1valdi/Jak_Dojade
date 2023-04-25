#pragma once
#include <initializer_list>
#include "String.h"

template <typename F, typename S>
class Pair {
public:
	Pair();
	Pair(F f, S s);
	F first;
	S secound;
	static Pair<F,S>& create(F f, S s);
};

template <typename F, typename S>
Pair<F,S>::Pair(F f, S s) {
	first = f;
	secound = s;
}

template <typename F, typename S>
Pair<F, S>::Pair() {}	// stay undefined

template <typename F, typename S>
Pair<F, S>& Pair<F, S>::create(F f, S s) {
	return *(new Pair<F, S>(f, s));
}

typedef Pair<String, int> siPair;