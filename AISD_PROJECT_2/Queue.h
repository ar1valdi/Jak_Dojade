#pragma once
#include "List.h"
#include "QueueNode.h"
#include <iostream>

template <typename T>
class Queue
{
	List<T> val;
public:
	void add(const T& v);
	T pop();
	bool isEmpty();
	int getSize();
};

template<typename T>
bool Queue<T>::isEmpty() {
	return val.isEmpty();
}
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
template <typename T>
int Queue<T>::getSize() {
	return val.getSize();
}