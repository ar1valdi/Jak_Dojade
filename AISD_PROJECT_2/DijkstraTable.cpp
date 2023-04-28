#include "DijkstraTable.h"
#include "DEFINES.h"

DijkstraTable::DijkstraTable(int size) {
	val = new List<siPair>[size];
}
int DijkstraTable::hash(const String& key) {
	unsigned long long sum = 0;

	for (int i = 0; i < key.getSize() - 1; i++) {	//-1 cuz of '\0', would bug with -47
		sum += ((int)key.getVal()[i] - 47) * pow(FIRST_NUMBER_FOR_HASHING, i);	//first valid character is 48, so reducing numbers reduces needed table space
	}

	return sum % HASH_TAB_SIZE;
}
void DijkstraTable::addCity(const String& name) {
	int id = hash(name);
	val[id].add(siPair::create(name, INF));
	ptrsToVals.add(&val[id].getLastNode()->getVal().secound);
}
void DijkstraTable::changeValue(const String& key, int dis) {
	getRightCity(key)->getVal().secound = dis;
}
void DijkstraTable::resetDistances() {
	Node<int*>* tmp = ptrsToVals.getFirstNode();
	while (tmp != nullptr) {
		*tmp->getVal() = INF;
		tmp = tmp->getNext();
	}
}
Node<siPair>* DijkstraTable::getRightCity(const String& key) {
	int id = hash(key);

	Node<siPair> *tmp = val[id].getFirstNode();

	while (tmp != nullptr && tmp->getVal().first != key) {
		tmp = tmp->getNext();
	}

	return tmp;
}
void DijkstraTable::print() {
	for (int i = 0; i < HASH_TAB_SIZE; i++) {
		auto* ptr = val[i].getFirstNode();

		while (ptr != nullptr) {
			std::cout << "(" << i << ")" << ptr->getVal().first.getVal() << ": " << ptr->getVal().secound;
			ptr = ptr->getNext();
			std::cout << "\n";
		}
	}
}
DijkstraTable::~DijkstraTable() {
	delete[] val;
}