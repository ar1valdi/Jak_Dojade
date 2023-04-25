#pragma once
#include "List.h"

template <typename T>
class Queue
{
	List<T> val;
public:
	void add(const T& v);
	T pop();
};

template <typename T>
void Queue<T>::add(const T& v) {
	val.add(v);
}
template <typename T>
T Queue<T>::pop() {
	T toRet = Move(val[0].getVal());
	val.del(0);
	return toRet;
}