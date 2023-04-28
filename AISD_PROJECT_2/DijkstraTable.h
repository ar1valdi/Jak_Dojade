#pragma once
#include "Pair.h"
#include "list.h"

class DijkstraTable
{
	List<siPair>* val;
	List<int*> ptrsToVals;
	
	int hash(const String& key);
	Node<siPair>* getRightCity(const String& key);
public:
	DijkstraTable(int size);
	void addCity(const String& name);
	void changeValue(const String& key, int dis);
	void resetDistances();

	//DEBUG PURPOSES, VERY SLOW BUT PRECISE
	void print();

	~DijkstraTable();
};