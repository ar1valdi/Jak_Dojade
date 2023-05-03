#pragma once
#include "List.h"
#include "PQNode.h"

struct PQdata {
    String* cityName;
    int dis;
    String* prev;
};

class PriorityQueue {
    PQdata* val;
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
    void add(String* name, int prio, String* prev);
    PQdata pop();
    int getSize() const;
    ~PriorityQueue();
};