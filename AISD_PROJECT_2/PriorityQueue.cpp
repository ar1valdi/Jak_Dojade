#include "PriorityQueue.h"
#include "CONTAINERS_CONSTS.h"

int PriorityQueue::min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

PriorityQueue::PriorityQueue() {
    val = new PQdata[DEF_VEC_SIZE];
    size = 0;
    allocatedSize = DEF_VEC_SIZE;
}

PriorityQueue::~PriorityQueue() {
    delete[] val;
}

void PriorityQueue::resize() {
    PQdata* tmp = val;

    allocatedSize *= 2;

    val = new PQdata[allocatedSize];

    for (int i = 0; i < size; i++) {
        val[i] = tmp[i];
    }
    delete[] tmp;
}

void PriorityQueue::add(String* name, int prio, String* prev) {
    if (size == allocatedSize)
        resize();

    val[size].cityName = name;
    val[size].dis = prio;
    val[size++].prev = prev;

    heapify(size-1, true);
}

PQdata PriorityQueue::pop() {
    PQdata toRet = Move(val[0]);
    val[0] = Move(val[size - 1]);
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
        printf(" %2d ", val[i-1].dis);
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
        minimal = val[L].dis;
    else
        minimal = min(val[L].dis, val[R].dis);

    if (minimal == val[L].dis)
        minID = L;
    else
        minID = R;

    if (minimal < val[id].dis) {
        PQdata helper = val[id];
        val[id] = val[minID];
        val[minID] = helper;

        int next = fromDown ? id : minID;
        heapify(next, fromDown);
    }
}
int PriorityQueue::getSize() const {
    return this->size;
}