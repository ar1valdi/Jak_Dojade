#pragma once
#include "Node.h"
#include "string.h"

template <typename T>
class List
{
protected:
	Node<T>* FirstNode;
	Node<T>* LastNode;
	int size;
public:
	List();
	List(const List<T>& other);
	List(List<T>&& other);
	void add(const T& val);
	int find(const T& val);
	Node<T>& find(const T& val, bool wantNode);
	bool del(const int& id);
	bool isEmpty() const;
	void clear();
	int getSize() const;
	Node<T>* getFirstNode() const;
	static List<T> emptyList();
	~List();

	Node<T>& operator[](size_t index);
	const Node<T>& operator[](size_t index) const;
	List<T>& operator=(const List<T>& l);
	List<T>& operator=(List<T>&& l);
};

template<typename T>
List<T> List<T>::emptyList() {
	List<T> empty;
	return empty;
}
template <typename T>
List<T>::List() {
	FirstNode = LastNode = nullptr;
	size = 0;
}
template <typename T>
List<T>::List(const List<T>& other) {
	FirstNode = LastNode = nullptr;
	*this = other;
}
template <typename T>
List<T>::List(List<T>&& other) {
	FirstNode = LastNode = nullptr;
	*this = Move<List>(other);
}
template <typename T>
int List<T>::getSize() const {
	return this->size;
}
template <typename T>
bool List<T>::isEmpty() const {
	if (this == nullptr || this->FirstNode == nullptr)
		return 1;
	return 0;
}
template <typename T>
Node<T>* List<T>::getFirstNode() const {
	return FirstNode;
}
template <typename T>
void List<T>::add(const T& val) {
	if (this->FirstNode == nullptr) {
		FirstNode = LastNode = new Node<T>;
		FirstNode->setVal(val);
		this->size++;
		return;
	}

	LastNode->setNext(new Node<T>);
	LastNode = LastNode->getNext();
	LastNode->setVal(val);
	LastNode->setNext(nullptr);
	this->size++;
}
template <typename T>
bool List<T>::del(const int& id) {
	if (this == nullptr || id >= this->size || id < 0)
		return 0;

	if (id == 0) {
		Node<T>* tmp = this->FirstNode;
		FirstNode = tmp->getNext();
		tmp->setNext(nullptr);
		delete tmp;
		this->size--;
		return 1;
	}

	Node<T>* tmp = &(*this)[id - 1];
	Node<T>* toAttach = tmp->getNext()->getNext();

	tmp->getNext()->setNext(nullptr);
	delete tmp->getNext();
	tmp->setNext(toAttach);

	if (toAttach == nullptr)		//if deleted node was the last one
		LastNode = tmp;
	this->size--;
	return 1;
}
// return -1 if not found
template <typename T>
int List<T>::find(const T& val) {
	if (this == nullptr || FirstNode == nullptr)
		return -1;

	Node<T>* tmp = FirstNode;
	int id = 0;
	while (tmp->getNext() != nullptr && tmp->val != val) {
		tmp = tmp->getNext();
		id++;
	}

	if (tmp->getNext() == nullptr && tmp->val != val) {
		return -1;
	}
	return id;
}
// returns empty node if not found
template <typename T>
Node<T>& List<T>::find(const T& val, bool wantNode) {
	if (FirstNode == nullptr) {
		Node<T>* emptyNode = new Node<T>;
		return *emptyNode;
	}

	Node<T>* tmp = FirstNode;
	while (tmp->getNext() != nullptr && tmp->val != val)
		tmp = tmp->getNext();

	if (tmp->getNext() == nullptr && tmp->val != val) {
		Node<T>* emptyNode = new Node<T>;
		return *emptyNode;
	}

	return *tmp;
}
template <typename T>
Node<T>& List<T>::operator[](size_t index) {
	Node<T>* tmp = this->FirstNode;
	for (std::size_t i = 0; i < index && tmp != nullptr; i++) {
		tmp = tmp->getNext();
	}
	return *tmp;
}
template <typename T>
const Node<T>& List<T>::operator[](size_t index) const {
	Node<T>* tmp = this->FirstNode;
	for (std::size_t i = 0; i < index && tmp != nullptr; i++) {
		tmp = tmp->getNext();
	}
	return *tmp;
}
template <typename T>
List<T>& List<T>::operator=(const List<T>& l) {
	this->size = l.size;

	if (this->size == 0) {
		FirstNode = LastNode = nullptr;
		return *this;
	}

	if (FirstNode != nullptr)
		delete FirstNode;
	FirstNode = new Node<T>;
	FirstNode->setVal(l.FirstNode->getVal());

	Node<T>* tmp = FirstNode;

	for (size_t i = 1; i < this->size; i++) {
		tmp->setNext(new Node<T>);
		tmp = tmp->getNext();
		tmp->setVal(l[i].getVal());
	}
	LastNode = tmp;
	return *this;
}
template <typename T>
void List<T>::clear() {
	FirstNode = nullptr;
	LastNode = nullptr;
	size = 0;
}
template <typename T>
List<T>& List<T>::operator=(List<T>&& l) {
	this->size = l.size;
	this->FirstNode = l.FirstNode;
	this->LastNode = l.LastNode;
	l.FirstNode = nullptr;
	l.LastNode = nullptr;
	return *this;
}
template <typename T>
List<T>::~List() {
	if (this != nullptr && FirstNode != nullptr)
		delete FirstNode;
}