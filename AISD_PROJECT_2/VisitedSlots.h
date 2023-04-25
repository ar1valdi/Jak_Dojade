#pragma once
#include "Pair.h"

class VisitedSlots
{
private:
	Pair<int, int>* slots;
	int size;
	int allocatedSize;
	void resize();
public:
	VisitedSlots();
	void add(int x, int y);
	int getSize();
	void clear();
	~VisitedSlots();

	Pair<int, int> operator[](int id);
};

