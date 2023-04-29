#pragma once
#include "Pair.h"
#include "list.h"


struct dijkstraData {
	String cityName;
	int dis;
	String prev;
};

class DijkstraTable
{
	List<dijkstraData>* val;
	List<int*> ptrsToVals;
	
	int hash(const String& key);
	Node<dijkstraData>* getRightCity(const String& key);
public:
	DijkstraTable(int size);
	void addCity(const String& name);
	void changeCity(const String& key, int dis, const String& prev);
	void resetDistances();
	dijkstraData operator[](const String& s);

	//DEBUG PURPOSES, VERY SLOW BUT PRECISE
	void print();

	~DijkstraTable();
};