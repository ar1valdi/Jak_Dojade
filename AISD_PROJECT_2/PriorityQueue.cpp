#include "PriorityQueue.h"
#include "CONTAINERS_CONSTS.h"
#include <math.h>

int PriorityQueue::min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

PriorityQueue::PriorityQueue() {
    val = new Pair<String,int>[DEF_VEC_SIZE];
    size = 0;
    allocatedSize = DEF_VEC_SIZE;
}

PriorityQueue::~PriorityQueue() {
    delete[] val;
}

void PriorityQueue::resize() {
    Pair<String, int>* tmp = val;

    allocatedSize *= 2;

    val = new Pair<String, int>[allocatedSize];

    for (int i = 0; i < size; i++) {
        val[i] = tmp[i];
    }
    delete[] tmp;
}

void PriorityQueue::add(const String& name, int prio) {
    if (size == allocatedSize)
        resize();

    val[size++] = Pair<String, int>::create(name, prio);
    heapify(size-1, true);
}

Pair<String, int> PriorityQueue::pop() {
    siPair toRet = Move(val[0]);
    val[0] = val[size - 1];
    size--;
    heapify(0, false);
    return toRet;
}

int PriorityQueue::left(int id) {
    return id * 2 + 1;
}
int PriorityQueue::right(int id) {
    return id * 2 + 2;
}
int PriorityQueue::parent(int id) {
    return (id - 1) / 2;
}

void PriorityQueue::printTree()
{
    int n = size;
    int i, j;
    int nextLvl = 0;
    int maxLvl = 0;
    int x = size;

    while (x != 0) {
        maxLvl++;
        x /= 2;
    }

    for (i = 1; i < size+1; i++)
    {
        if (i == 1 << nextLvl) {
            printf("\n");
            nextLvl += 1;
            for (j = 0; j < (1 << (maxLvl - nextLvl)) - 1; j++) printf("  ");
        }
        printf(" %2d ", val[i-1].secound);
        for (j = 0; j < (1 << (maxLvl - nextLvl)) - 1; j++) printf("    ");
    }
}

void PriorityQueue::heapify(int i, bool fromDown) {
    if (size == 1 || (left(i) >= size && !fromDown))
        return;

    int id = fromDown ? parent(i) : i;

    int L = left(id);
    int R = right(id);
    int minID, minimal;

    if (R >= size)
        minimal = val[L].secound;
    else
        minimal = min(val[L].secound, val[R].secound);

    if (minimal == val[L].secound)
        minID = L;
    else
        minID = R;

    if (minimal < val[id].secound) {
        Pair<String, int> helper = val[id];
        val[id] = val[minID];
        val[minID] = helper;

        int next = fromDown ? id : minID;
        heapify(next, fromDown);
    }
}
int PriorityQueue::getSize() const {
    return this->size;
}