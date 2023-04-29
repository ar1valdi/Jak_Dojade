#include "DijkstraTable.h"
#include "DEFINES.h"

DijkstraTable::DijkstraTable(int size) {
	val = new List<dijkstraData>[size];
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
	val[id].add({name, (int)INF, NO_PREV_CITIES});
	ptrsToVals.add(&val[id].getLastNode()->getVal().dis);
}
void DijkstraTable::changeCity(const String& key, int dis, const String& prev) {
	dijkstraData* inner = &getRightCity(key)->getVal();
	inner->dis = dis;
	inner->prev = prev;
}
void DijkstraTable::resetDistances() {
	Node<int*>* tmp = ptrsToVals.getFirstNode();
	while (tmp != nullptr) {
		*tmp->getVal() = INF;
		tmp = tmp->getNext();
	}
}
Node<dijkstraData>* DijkstraTable::getRightCity(const String& key) {
	int id = hash(key);

	Node<dijkstraData> *tmp = val[id].getFirstNode();

	while (tmp != nullptr && tmp->getVal().cityName != key) {
		tmp = tmp->getNext();
	}

	return tmp;
}
void DijkstraTable::print() {
	for (int i = 0; i < HASH_TAB_SIZE; i++) {
		auto* ptr = val[i].getFirstNode();

		while (ptr != nullptr) {
			std::cout << "(" << i << ")" << ptr->getVal().cityName.getVal() << ": " << ptr->getVal().dis;
			std::cout << ", " << ptr->getVal().prev.getVal();
			ptr = ptr->getNext();
			std::cout << "\n";
		}
	}
}
dijkstraData DijkstraTable::operator[](const String& s) {
	return getRightCity(s)->getVal();
}
DijkstraTable::~DijkstraTable() {
	delete[] val;
}