#include "DijkstraTable.h"
#include "DEFINES.h"

DijkstraTable::DijkstraTable(int size, HashTable* ht) {
	val = new List<dijkstraData>[size];
	this->ht = ht;
	NO_PREV = NO_PREV_CITIES;
}
int DijkstraTable::hash(const String& key) {
	unsigned long long sum = 0;
	char* ch = key.getVal();

	while (*ch) {
		sum = (sum << BIT_SHIFT_HASH) + *(ch++);
	}

	return sum % HASH_TAB_SIZE;
}
void DijkstraTable::addCity(const String& name) {
	int id = hash(name);
	dijkstraData dD;
	dD.cityName = ht->getCityStringPtr(name);
	dD.dis = (int)INF;
	dD.prev = &NO_PREV;

	val[id].add(dD);
	ptrsToVals.add(&val[id].getLastNode()->getVal().dis);
	ptrsToVisits.add(&val[id].getLastNode()->getVal().visited);
}
void DijkstraTable::changeCity(const String& key, int dis, const String& prev) {
	dijkstraData* inner = &getRightCity(key)->getVal();
	inner->dis = dis;
	inner->prev = ht->getCityStringPtr(prev);
	inner->visited = false;
}
void DijkstraTable::firstCity(const String& key) {
	dijkstraData* inner = &getRightCity(key)->getVal();
	inner->dis = 0;
	inner->prev = &NO_PREV;
	inner->visited = false;
}
void DijkstraTable::resetDistances() {
	Node<int*>* tmp = ptrsToVals.getFirstNode();
	Node<bool*>* tmpVis = ptrsToVisits.getFirstNode();
	while (tmp != nullptr) {
		*tmp->getVal() = INF;
		*tmpVis->getVal() = false;
		tmp = tmp->getNext();
		tmpVis = tmpVis->getNext();
	}
}
Node<dijkstraData>* DijkstraTable::getRightCity(const String& key) {
	int id = hash(key);

	Node<dijkstraData> *tmp = val[id].getFirstNode();

	while (tmp != nullptr && *tmp->getVal().cityName != key) {
		tmp = tmp->getNext();
	}

	return tmp;
}
void DijkstraTable::print() {
	for (int i = 0; i < HASH_TAB_SIZE; i++) {
		auto* ptr = val[i].getFirstNode();

		while (ptr != nullptr) {
			std::cout << "(" << i << ")" << ptr->getVal().cityName->getVal() << ": " << ptr->getVal().dis;
			std::cout << ", " << ptr->getVal().prev->getVal();
			ptr = ptr->getNext();
			std::cout << "\n";
		}
	}
}
dijkstraData& DijkstraTable::operator[](const String& s) {
	return getRightCity(s)->getVal();
}
DijkstraTable::~DijkstraTable() {
	delete[] val;
}