#pragma once
#include "Pair.h"

class QueueNode
{
public:
	Pair<int, int> pos;
	int distance;
	QueueNode();
	QueueNode(int x, int y, int dis);
	static QueueNode create(int x, int y, int dis);
};