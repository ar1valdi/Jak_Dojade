#include "QueueNode.h"

QueueNode::QueueNode() {
	pos.first = 0;
	pos.secound = 0;
	distance = 0;
}
QueueNode::QueueNode(int x, int y, int dis) {
	pos.first = x;
	pos.secound = y;
	distance = dis;
}
QueueNode QueueNode::create(int x, int y, int dis) {
	QueueNode q(x, y, dis);
	return q;
}