#pragma once
#include "List.h"
#include "PQNode.h"

class PriorityQueue {
    Pair<String, int>* val;
    int size, allocatedSize;
    int left(int id);
    int right(int id);
    int parent(int id);
    int min(int a, int b);
    void heapify(int id, bool fromDown);
    void resize();

public:
    PriorityQueue();
    void printTree();
    void add(const String& name, int prio);
    Pair<String, int> pop();
    int getSize() const;
    ~PriorityQueue();
};