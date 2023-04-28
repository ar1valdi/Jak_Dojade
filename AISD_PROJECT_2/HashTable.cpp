#include "HashTable.h"
#include "Pair.h"
#include "DEFINES.h"

HashTable::HashTable(int size) {
	arr = new List<Pair<String, List < siPair >>>[size];
}
int HashTable::hash(const String& key) {
	unsigned long long sum = 0;

	for (int i = 0; i < key.getSize() - 1; i++) {	//-1 cuz of '\0', would bug with -47
		sum += ((int)key.getVal()[i] - 47) * pow(FIRST_NUMBER_FOR_HASHING,i);	//first valid character is 48, so reducing numbers reduces needed table space
	}

	return sum % HASH_TAB_SIZE;
}
void HashTable::addToId(int id, const String& key, const List< siPair >& val) {
	arr[id].add(Pair<String, List< siPair >>::create( key, val ));
}
void HashTable::addList(const String& key, const List< siPair >& val) {
	int id = hash(key);
	addToId(id, key, val);
}
Node<Pair<String, List < siPair >>>* HashTable::getRightCity(const String& key) {
	int id = hash(key);

	Node<Pair<String, List < siPair >>>* tmp = arr[id].getFirstNode();

	while (tmp != nullptr && tmp->getVal().first != key) {
		tmp = tmp->getNext();
	}

	return tmp;
}
const List< siPair >& HashTable::getAllConnections(const String& key){
	Node<Pair<String, List<siPair>>>* tmp = getRightCity(key);

	return tmp->getVal().secound;
}
void HashTable::addConnection(const String& key, const String& city, int distance) {
	Node<Pair<String, List<siPair>>>* tmp = getRightCity(key);

	if (tmp == nullptr)
		return;	

	tmp->getVal().secound.add(siPair::create(city, distance));
}
void HashTable::addCity(const String& key) {
	int id = hash(key);
	arr[id].add(Pair<String, List<siPair>>::create(key, List<siPair>::emptyList()));
}
void HashTable::print() {
	for (int i = 0; i < HASH_TAB_SIZE; i++) {
		auto* ptr = arr[i].getFirstNode();

		while (ptr != nullptr) {
			std::cout << "(" << i << ")" << ptr->getVal().first.getVal() << ": ";
			auto* ptrInside = ptr->getVal().secound.getFirstNode();
			while (ptrInside != nullptr) {
				std::cout << ptrInside->getVal().first.getVal() << " - " << ptrInside->getVal().secound << ", ";
				ptrInside = ptrInside->getNext();
			}
			ptr = ptr->getNext();
			std::cout << "\n";
		}
	}
}
HashTable::~HashTable() {
	delete[] arr;
}