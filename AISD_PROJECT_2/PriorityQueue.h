#pragma once
#include "List.h"
#include "PQNode.h"

class PriorityQueue {
	List<PQNode> val;
public:
	void add(Pair<int,int> val, int prio);
	Pair<int,int> pop();
};

Pair<int,int> PriorityQueue::pop() {
	Pair<int,int> toReturn = val[0].getVal().val;
	val.del(0);
	return toReturn;
}

void PriorityQueue::add(Pair<int,int> v, int prio) {
	PQNode toAdd;
	toAdd.val = v;
	toAdd.priority = prio;
	Node<PQNode>* tmpNode = val.getFirstNode();

	if (val.getSize() == 0) {
		val.add(toAdd);
		return;
	}

	if (tmpNode->getVal().priority >= prio) {
		Node<PQNode>* newNode = new Node<PQNode>;
		newNode->setVal(toAdd);
		newNode->setNext(tmpNode);
		val.FirstNode = newNode;
		val.size++;
		return;
	}

	bool added = false;
	Node<PQNode>* checkNext;

	int sizeBefore = val.getSize();

	for (int i = 0; i < sizeBefore - 1; i++) {
		checkNext = tmpNode->getNext();

		if (checkNext->getVal().priority >= prio) {
			Node<PQNode>* newNode = new Node<PQNode>;
			newNode->setVal(toAdd);
			newNode->setNext(tmpNode->getNext());
			tmpNode->setNext(newNode);
			val.size++;
			added = true;
			break;
		}
		if (sizeBefore - 1 != i + 1)
			tmpNode = tmpNode->getNext();
	}

	if (!added) {
		Node<PQNode>* newNode = new Node<PQNode>;
		newNode->setVal(toAdd);
		if (val.LastNode->getVal().priority <= prio) {
			newNode->setNext(nullptr);
			val.LastNode->setNext(newNode);
			val.LastNode = newNode;
			val.size++;
		}
		else {
			newNode->setNext(val.LastNode);
			tmpNode->setNext(newNode);
			val.size++;
		}
	}
}