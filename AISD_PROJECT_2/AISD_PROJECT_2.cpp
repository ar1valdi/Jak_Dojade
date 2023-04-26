#include <iostream>
#include "List.h"
#include "operators.h"
#include "Pair.h"
#include "HashTable.h"
#include "DEFINES.h"
#include "Pair.h"
#include "Queue.h"
#include "QueueNode.h"
#include "VisitedSlots.h"
#include <stdio.h>
#include "PriorityQueue.h"

char** enterField(int &w, int &h, List<Pair<int,int>>& cities) {
	std::cin >> w >> h;

	char** field;
	field = new char* [w];

	for (int i = 0; i < w; i++) {
		field[i] = new char[h];
	}

	getchar();	// burn '\n' that is left
	for (int i = 0; i < h; i++) {

		for (int j = 0; j < w; j++) {

			field[j][i] = getchar();
			if (field[j][i] == '*') {
				cities.add(Pair<int, int>::create(j, i));
			}

		}
		getchar();	// burn '\n' that is left
	}

	return field;
}
bool isCityChar(char c) {
	if (isdigit(c) || isalpha(c))
		return true;
	return false;
}
bool isFirstOrLastLetterOfCity(int x, int y, int w, char** field) {
	if (!isCityChar(field[x][y]))
		return false;

	if (x - 1 < 0 || x + 1 == w)
		return true;

	if (!isCityChar(field[x - 1][y]) || !isCityChar(field[x + 1][y]))
		return true;

	return false;
}
bool isInMap(int x, int y, int w, int h) {
	if (x >= 0 && x < w && y >= 0 && y < h)
		return true;
	return false;
}
String getCityString(int x, int y, int w, char** field) {
	
	String name;

	if (x + 1 == w || (x + 1 < w && !isCityChar(field[x + 1][y]))) {
		while (x >= 0 && (isdigit(field[x][y]) || isalpha(field[x][y]))) {
			x--;
		}

		x += 1;
	}

	while (x < w && (isdigit(field[x][y]) || isalpha(field[x][y]))) {
		name += field[x][y];
		x++;
	}

	return name;
}
String getCityName(int x, int y, int w, int h, char ** field) {
	String name;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
	
			int tmpX = x + i;
			int tmpY = y + j;
	
			if (!isInMap(tmpX, tmpY, w, h)) continue;
			if (!isFirstOrLastLetterOfCity(tmpX, tmpY, w, field)) continue;

			name = getCityString(tmpX, tmpY, w, field);
			break;
		}
	}
	return name;
}
void printDebug(char** field, int w, int h, bool** bm) {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (bm[j][i] == 0)
				putchar(field[j][i]);
			else
				putchar('O');
		}
		putchar('\n');
	}
}
void connectCities(Queue<QueueNode>& toCheck, int w, int h, bool** visitedBoolMap, char** field, HashTable& ht, String& name, VisitedSlots& visitedVector) {

	Pair<int, int> dirs[4] = { Pair<int,int>::create(-1,0), Pair<int,int>::create(1,0), Pair<int,int>::create(0, -1), Pair<int,int>::create(0, 1) };

	while (!toCheck.isEmpty()) {

		QueueNode node = toCheck.pop();

		for (Pair<int, int> dir : dirs) {
			int checkX = node.pos.first + dir.first;
			int checkY = node.pos.secound + dir.secound;

			if (isInMap(checkX, checkY, w, h) && !visitedBoolMap[checkX][checkY]) {
				if (field[checkX][checkY] == ROAD_ASCII) {
					toCheck.add(*(QueueNode::create(checkX, checkY, node.distance + 1)));

					visitedVector.add(checkX, checkY);
					visitedBoolMap[checkX][checkY] = 1;
				}
				else if (field[checkX][checkY] == CITY_ASCII)
					ht.addConnection(name, getCityName(checkX, checkY, w, h, field), node.distance);

			}
		}

		//char buf;
		//std::cin >> buf;
		//printDebug(field, w, h, visitedBoolMap);
		//std::cout << node.pos.first << " " << node.pos.secound << '\n';
	}
}
void clearVisited(bool** visitedBoolMap, VisitedSlots& visitedVector) {
	for (int i = 0; i < visitedVector.getSize(); i++) {
		visitedBoolMap[visitedVector[i].first][visitedVector[i].secound] = 0;
	}
	visitedVector.clear();
}
void loadGraph(HashTable& ht, char** field, List<Pair<int,int>>& cities, int w, int h) {

	Node<Pair<int, int>>* tmp = cities.getFirstNode();
	String name;
	Queue<QueueNode> toCheck;
	bool** visitedBoolMap;
	VisitedSlots visitedVector;

	visitedBoolMap = new bool*[w];
	for (int i = 0; i < w; i++) {
		visitedBoolMap[i] = new bool[h];
		for (int j = 0; j < h; j++)
			visitedBoolMap[i][j] = 0;
	}

	for (int i = 0; i < cities.getSize(); i++) {
		Pair<int, int> cityPos = tmp->getVal();

		name = getCityName(cityPos.first, cityPos.secound, w, h, field);
		ht.addCity(name);

		toCheck.add(*(QueueNode::create(cityPos.first, cityPos.secound, 0)));
		
		visitedVector.add(cityPos.first, cityPos.secound);
		visitedBoolMap[cityPos.first][cityPos.secound] = 1;

		connectCities(toCheck, w, h, visitedBoolMap, field, ht, name, visitedVector);
		clearVisited(visitedBoolMap, visitedVector);

		tmp = tmp->getNext();
	}
}
void loadFlights(HashTable& ht) {
	int num, dis;
	String from, to;
	std::cin >> num;
	
	for (int i = 0; i < num; i++) {
		getchar(); // burn '\n' leftover
		std::cin >> from >> to >> dis;
		std::cout << "F: " << from << " T: " << to << " D: " << dis << '\n';
		ht.addConnection(from, to, dis);
	}
}


int main(){
	//PriorityQueue pq;
	//pq.add(Pair<int, int>::create(0, 4), 4);
	//pq.add(Pair<int, int>::create(0, 3), 3);
	//pq.add(Pair<int, int>::create(0, 2), 2);
	//pq.add(Pair<int, int>::create(0, 1), 1);
	//pq.add(Pair<int, int>::create(0, 6), 6);
	//pq.add(Pair<int, int>::create(0, 5), 5);
	//pq.add(Pair<int, int>::create(0, 4), 4);
	//pq.add(Pair<int, int>::create(0, 3), 3);
	//pq.add(Pair<int, int>::create(0, 2), 2);
	//pq.add(Pair<int, int>::create(0, 1), 1);
	//
	//pq.add(Pair<int, int>::create(0, 6), 6);
	//pq.add(Pair<int, int>::create(0, 5), 5);
	//pq.add(Pair<int, int>::create(0, 4), 4);
	//pq.add(Pair<int, int>::create(0, 3), 3);
	//
	//for (int i = 0; i < 14; i++) {
	//	Pair<int, int> toRead = pq.pop();
	//	std::cout << toRead.first << " " << toRead.secound << '\n';	
	//}
	//
	//return 0;
	HashTable tab(SIZE_FOR_20_CHARS);

	char** field;
	int w, h;
	List<Pair<int, int>> citiesPos;
	field = enterField(w, h, citiesPos);

	std::cout << '\n';
	std::cout << '\n';
	
	for (int i = 0; i < citiesPos.getSize(); i++) {
		std::cout << citiesPos[i].getVal().first << " ";
		std::cout << citiesPos[i].getVal().secound << " ";
		std::cout << field[citiesPos[i].getVal().first][citiesPos[i].getVal().secound] << "\n";
	}

	loadGraph(tab, field, citiesPos, w, h);
	loadFlights(tab);

	tab.print();
}