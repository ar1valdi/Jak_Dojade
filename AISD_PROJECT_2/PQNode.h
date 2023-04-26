#pragma once
#include "Pair.h"

class PQNode {
	int priority;
	Pair<int,int> val;
	friend class PriorityQueue;
};