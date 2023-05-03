#include "HashTable.h"
#include "Pair.h"
#include "DEFINES.h"

HashTable::HashTable(int size) {
	arr = new List<Pair<String, List < psiPair >>>[size];
}
int HashTable::hash(const String& key) {
	unsigned long long sum = 0;
	char* ch = key.getVal();

	while (*ch) {
		sum = (sum << BIT_SHIFT_HASH) + *(ch++);
	}

	//for (int i = 0; i < key.getSize() - 1; i++) {	//-1 cuz of '\0', would bug with -47
	//	sum += ((int)key.getVal()[i] - 47) * (pow(FIRST_NUMBER_FOR_HASHING, i));	//first valid character is 48, so reducing numbers reduces needed table space
	//}

	return sum % HASH_TAB_SIZE;
}
void HashTable::addToId(int id, const String& key, const List< psiPair >& val) {
	arr[id].add(Pair<String, List< psiPair >>::create( key, val ));
}
void HashTable::addList(const String& key, const List< psiPair >& val) {
	int id = hash(key);
	addToId(id, key, val);
}
String* HashTable::getCityStringPtr(const String& key) {
	return &(getRightCity(key)->getVal().first);
}
Node<Pair<String, List < psiPair >>>* HashTable::getRightCity(const String& key) {
	int id = hash(key);

	Node<Pair<String, List < psiPair >>>* tmp = arr[id].getFirstNode();

	while (tmp != nullptr && tmp->getVal().first != key) {
		tmp = tmp->getNext();
	}

	return tmp;
}
List< psiPair >& HashTable::getAllConnections(const String& key){
	Node<Pair<String, List<psiPair>>>* tmp = getRightCity(key);

	return tmp->getVal().secound;
}
void HashTable::addConnection(const String& key, String* city, int distance) {
	Node<Pair<String, List<psiPair>>>* tmp = getRightCity(key);

	if (tmp == nullptr)
		return;	

	tmp->getVal().secound.add(psiPair::create(city, distance));
}
void HashTable::addCity(const String& key) {
	int id = hash(key);
	arr[id].add(Pair<String, List<psiPair>>::create(key, List<psiPair>::emptyList()));
}
void HashTable::print() {
	for (int i = 0; i < HASH_TAB_SIZE; i++) {
		auto* ptr = arr[i].getFirstNode();

		while (ptr != nullptr) {
			std::cout << "(" << i << ")" << ptr->getVal().first.getVal() << ": ";
			auto* ptrInside = ptr->getVal().secound.getFirstNode();
			while (ptrInside != nullptr) {
				std::cout << ptrInside->getVal().first->getVal() << " - " << ptrInside->getVal().secound << ", ";
				ptrInside = ptrInside->getNext();
			}
			ptr = ptr->getNext();
			std::cout << "\n";
		}
	}
}
int HashTable::getAdjLength(const String& from, const String& to) {
	List<psiPair>* connections = &getAllConnections(from);

	Node<psiPair>* tmp = connections->getFirstNode();

	while (tmp != nullptr) {
		if (*tmp->getVal().first == to)
			return tmp->getVal().secound;
		tmp = tmp->getNext();
	}

	return -1;
}
HashTable::~HashTable() {
	delete[] arr;
}