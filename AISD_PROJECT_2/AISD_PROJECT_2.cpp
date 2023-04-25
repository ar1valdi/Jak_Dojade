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

		while ((isdigit(field[x][y]) || isalpha(field[x][y])) && x != -1) {
			x--;
		}

		x += 1;
	}

	while (isdigit(field[x][y]) || isalpha(field[x][y])) {
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
void loadGraph(HashTable& ht, char** field, List<Pair<int,int>>& cities, int w, int h) {

	Node<Pair<int, int>>* tmp = cities.getFirstNode();
	String name;
	VisitedSlots visitedVector;
	Queue<QueueNode> toCheck;
	bool** visitedBoolMap;

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

		Pair<int, int> dirs[4] = { Pair<int,int>::create(-1,0), Pair<int,int>::create(1,0), Pair<int,int>::create(0, -1), Pair<int,int>::create(0, 1) };
		toCheck.add(*(QueueNode::create(cityPos.first, cityPos.secound, 0)));

		while (!toCheck.isEmpty()) {

			QueueNode node = toCheck.pop();

			for (Pair<int, int> dir : dirs) {
				int checkX = node.pos.first + dir.first;
				int checkY = node.pos.secound + dir.secound;

				if (isInMap(checkX, checkY, w, h) && !visitedBoolMap[checkX][checkY]) {
					if (field[checkX][checkY] == ROAD_ASCII)
						toCheck.add(*(QueueNode::create(checkX, checkY, node.distance + 1)));
					else if (field[checkX][checkY] == CITY_ASCII)
						ht.addConnection(name, getCityName(checkX, checkY, w, h, field), node.distance);

				}
			}

			visitedVector.add(node.pos.first, node.pos.secound);
			visitedBoolMap[node.pos.first][node.pos.secound] = 1;

			std::cout << "node: " << node.pos.first << " " << node.pos.secound << '\n';
		}

		//clear the visted map
		for (int i = 0; i < visitedVector.getSize(); i++) {
			visitedBoolMap[visitedVector[i].first][visitedVector[i].secound] = 0;
		}
		visitedVector.clear();

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

	//std::cout << '\n';
	//std::cout << '\n';
	//
	//for (int i = 0; i < h; i++) {
	//	for(int j =0; j < w; j++)
	//		std::cout << field[j][i];
	//	std::cout << '\n';
	//}
}