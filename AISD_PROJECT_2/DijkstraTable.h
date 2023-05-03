#pragma once
#include "Pair.h"
#include "list.h"
#include "HashTable.h"

struct dijkstraData {
	String* cityName;
	int dis;
	String* prev;
	bool visited = false;
};

class DijkstraTable
{
	List<dijkstraData>* val;
	List<int*> ptrsToVals;
	List<bool*> ptrsToVisits;
	HashTable* ht;
	String NO_PREV;

	int hash(const String& key);
	Node<dijkstraData>* getRightCity(const String& key);
public:
	DijkstraTable(int size, HashTable* ht);
	void addCity(const String& name);
	void changeCity(const String& key, int dis, const String& prev);
	void setFirstCity(const String& key);
	void resetDistances();
	dijkstraData& operator[](const String& s);

	//DEBUG PURPOSES, VERY SLOW BUT PRECISE
	void print();

	~DijkstraTable();
};