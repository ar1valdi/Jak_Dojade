#pragma once
#include "CONTAINERS_CONSTS.h"
#include "String.h"
#include "List.h"
#include "Pair.h"

class HashTable {
private:
	List<Pair<String, List < siPair >>>* arr;

	/*
	val = [0] -> [key][list of pairs<string, list<d1, d2>>]
		  [1] ->  ------------ | | ---------------
		 ...
		  [n] -> ------------- | | ---------------
	*/

	int hash(const String& key);	//returns id in table
	void addToId(int id, const String& key, const List< siPair >& val);	//handles colls
	Node<Pair<String, List < siPair >>>* getRightCity(const String& key);
public:
	HashTable(int size);
	void addList(const String& key, const List< siPair >& val);
	void addCity(const String& key);
	void addConnection(const String& key, const String& city, int distance);
	const List< siPair >& getAllConnections(const String& key);

	//DEBUG PURPOSES, VERY SLOW BUT PRECISE
	void print();
	
	~HashTable();
};