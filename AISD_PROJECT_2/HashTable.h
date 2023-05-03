#pragma once
#include "CONTAINERS_CONSTS.h"
#include "String.h"
#include "List.h"
#include "Pair.h"

class HashTable {
private:
	List<Pair<String, List < psiPair >>>* arr;

	/*
	val = [0] -> [key][list of pairs<string, list<d1, d2>>]
		  [1] ->  ------------ | | ---------------
		 ...
		  [n] -> ------------- | | ---------------
	*/

	int hash(const String& key);	//returns id in table
	void addToId(int id, const String& key, const List< psiPair >& val);	//handles colls
	Node<Pair<String, List < psiPair >>>* getRightCity(const String& key);
public:
	HashTable(int size);
	void addList(const String& key, const List< psiPair >& val);
	void addCity(const String& key);
	void addConnection(const String& key, String* city, int distance);
	int getAdjLength(const String& from, const String& to);
	String* getCityStringPtr(const String& key);
	List< psiPair >& getAllConnections(const String& key);

	//DEBUG PURPOSES, VERY SLOW BUT PRECISE
	void print();
	
	~HashTable();
};