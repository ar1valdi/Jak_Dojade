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
	static Pair<F,S> create(const F& f, const S& s);
};

template <typename F, typename S>
Pair<F,S>::Pair(F f, S s) {
	first = f;
	secound = s;
}

template <typename F, typename S>
Pair<F, S>::Pair() {
	
}

template <typename F, typename S>
Pair<F, S> Pair<F, S>::create(const F& f,const S& s) {
	Pair<F, S> p;
	p.first = f;
	p.secound = s;
	return p;
}

typedef Pair<String, int> siPair;
typedef Pair<String*, int> psiPair;