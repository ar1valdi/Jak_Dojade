#pragma once
#include "String.h"
#include "Move.h"

template <typename T>
class Node
{
private:
	T val;
	Node* next;
	friend std::ostream& operator<<(std::ostream& out, const Node& n);
public:
	Node();
	Node(const Node& right);
	Node(Node&& right);
	const T& getVal() const;
	T& getVal();
	T getValCopy() const;
	void setVal(const T& newV);
	Node<T>* getNext();
	void setNext(Node<T>* newN);
	~Node();

	Node<T>& operator=(Node<T>* other) {
		val = other->val;
		next = other->next;
		return *this;
	}
};


template <typename T>
Node<T>::Node() {
	this->next = nullptr;
}
template <typename T>
Node<T>::Node(const Node& right) {
	val = right.val;
	next = right.next;
}
template <typename T>
Node<T>::Node(Node&& right) {
	val = Move<String>(right.val);
	next = right.next;
}
template <typename T>
T Node<T>::getValCopy() const {
	return this->val;
}
template <typename T>
const T& Node<T>::getVal() const {
	return this->val;
}
template <typename T>
T& Node<T>::getVal() {
	return this->val;
}
template <typename T>
void Node<T>::setVal(const T& newV) {
	this->val = newV;
}
template <typename T>
Node<T>* Node<T>::getNext() {
	return this->next;
}
template <typename T>
void Node<T>::setNext(Node<T>* newN) {
	this->next = newN;
}
template <typename T>
Node<T>::~Node() {
	if (this != nullptr && next != nullptr)
		delete next;
}
