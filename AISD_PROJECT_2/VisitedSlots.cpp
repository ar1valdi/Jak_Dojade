#include "VisitedSlots.h"
#include "CONTAINERS_CONSTS.h"

VisitedSlots::VisitedSlots() {
	slots = new Pair<int, int>[DEF_VEC_SIZE];
	size = 0;
	allocatedSize = DEF_VEC_SIZE;
}
void VisitedSlots::resize() {
	Pair<int, int>* tmp = slots;

	allocatedSize *= 2;

	slots = new Pair<int, int>[allocatedSize];

	for (int i = 0; i < size; i++) {
		slots[i] = tmp[i];
	}
}
void VisitedSlots::add(int x, int y) {
	if (size == allocatedSize)
		resize();

	slots[size++] = Pair<int, int>::create(x,y);
}
VisitedSlots::~VisitedSlots() {
	delete[] slots;
}
Pair<int, int> VisitedSlots::operator[](int id) {
	return slots[id];
}
int VisitedSlots::getSize() {
	return size;
}
void VisitedSlots::clear() {
	delete slots;
	slots = new Pair<int, int>[DEF_VEC_SIZE];
	size = 0;
	allocatedSize = DEF_VEC_SIZE;
}