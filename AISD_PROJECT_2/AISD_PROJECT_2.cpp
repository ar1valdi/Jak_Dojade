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
#include "DijkstraTable.h"

char** enterField(int &w, int &h, List<Pair<int,int>>& cities) {
	std::cin >> w >> h;

	char** field;
	field = new char* [w];

	for (int i = 0; i < w; i++) {
		field[i] = new char[h];
	}

	_getchar_nolock();	// burn '\n' that is left
	for (int i = 0; i < h; i++) {

		for (int j = 0; j < w; j++) {

			field[j][i] = _getchar_nolock();
			if (field[j][i] == '*') {
				cities.add(Pair<int, int>::create(j, i));
			}

		}
		_getchar_nolock();	// burn '\n' that is left
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
					toCheck.add(QueueNode::create(checkX, checkY, node.distance + 1));

					visitedVector.add(checkX, checkY);
					visitedBoolMap[checkX][checkY] = 1;
				}
				else if (field[checkX][checkY] == CITY_ASCII) {
					String* toAdd = ht.getCityStringPtr(getCityName(checkX, checkY, w, h, field));
					ht.addConnection(name, toAdd, node.distance + 1);

					visitedVector.add(checkX, checkY);
					visitedBoolMap[checkX][checkY] = 1;
				}
			}
		}
	}
}
void clearVisited(bool** visitedBoolMap, VisitedSlots& visitedVector) {
	for (int i = 0; i < visitedVector.getSize(); i++) {
		visitedBoolMap[visitedVector[i].first][visitedVector[i].secound] = 0;
	}
	visitedVector.clear();
}
void loadGraph(HashTable& ht, char** field, List<Pair<int,int>>& cities, int w, int h, DijkstraTable& dt) {

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
	while(tmp != nullptr) {
		Pair<int, int> cityPos = tmp->getVal();

		// add city to hashmap representing graph
		name = getCityName(cityPos.first, cityPos.secound, w, h, field);
		ht.addCity(name);
		dt.addCity(name);

		tmp = tmp->getNext();
	}

	tmp = cities.getFirstNode();

	while(tmp != nullptr) {
		Pair<int, int> cityPos = tmp->getVal();
		name = getCityName(cityPos.first, cityPos.secound, w, h, field);

		toCheck.add(QueueNode::create(cityPos.first, cityPos.secound, 0));
		
		visitedVector.add(cityPos.first, cityPos.secound);
		visitedBoolMap[cityPos.first][cityPos.secound] = 1;
		
		connectCities(toCheck, w, h, visitedBoolMap, field, ht, name, visitedVector);
		clearVisited(visitedBoolMap, visitedVector);

		tmp = tmp->getNext();
	}

	for (int i = 0; i < w; i++)
		delete[] visitedBoolMap[i];
	delete[] visitedBoolMap;
}
void loadFlights(HashTable& ht) {
	int num, dis;
	String from, to;
	scanf_s("%d", &num);
	
	for (int i = 0; i < num; i++) {
		_getchar_nolock(); // burn '\n' leftover
		from.getword();
		to.getword();
		scanf_s("%d", &dis);
		ht.addConnection(from, ht.getCityStringPtr(to), dis);
	}
}
void getPath(DijkstraTable& dt, const String& from, const String& to, List<String>& path) {
	String prevCity = to;

	while (*dt[prevCity].prev != from && *dt[prevCity].prev != NO_PREV_CITIES) {
		prevCity = *dt[prevCity].prev;
		path.insertFirst(prevCity);
	}
}
void shortestPath(String& from, const String& to, HashTable& ht, DijkstraTable& distances) {
	distances.resetDistances();
	PriorityQueue pq;
	PQdata curCity;
	dijkstraData* nextCity;
	List<psiPair>* adj;
	Node<psiPair>* cityToCheck;
	int roadLen, disToCurr;

	distances.setFirstCity(from);

	adj = &ht.getAllConnections(from);
	cityToCheck = adj->getFirstNode();

	// add surroundings of from to pq
	while (cityToCheck != nullptr) {
		pq.add(cityToCheck->getVal().first, cityToCheck->getVal().secound, &from);
		cityToCheck = cityToCheck->getNext();
	}

	// dijkstra's algorithm
	while (pq.getSize() != 0) {
		curCity = pq.pop();

		adj = &ht.getAllConnections(*curCity.cityName);
		cityToCheck = adj->getFirstNode();

		disToCurr = curCity.dis;
		if (distances[*curCity.cityName].dis > disToCurr)
			distances.changeCity(*curCity.cityName, disToCurr, *curCity.prev);
		else
			continue;

		if (*curCity.cityName == to) break;

		while (cityToCheck != nullptr) {

			roadLen = cityToCheck->getVal().secound;

			nextCity = &distances[*cityToCheck->getVal().first];

			if (nextCity->dis > disToCurr + roadLen && !nextCity->visited)
				pq.add(cityToCheck->getVal().first, disToCurr + roadLen, curCity.cityName);

			cityToCheck = cityToCheck->getNext();
		}

	}
}
void printOutput(DijkstraTable& distances, const String& from, const String& to, int mode) {
	std::cout << distances[to].dis;

	if (mode == 1) {
		List<String> path;
		getPath(distances, from, to, path);

		Node<String>* tmp = path.getFirstNode();
		while (tmp != nullptr) {
			std::cout << " " << tmp->getVal().getVal();
			tmp = tmp->getNext();
		}
	}
	std::cout << '\n';
}
void handleCommands(HashTable& ht, DijkstraTable& dt) {
	int num, mode;
	String from, to;
	scanf_s("%d", &num);

	for (int i = 0; i < num; i++) {
		_getchar_nolock();	// burn '\n' leftover
		from.getword();
		to.getword();
		scanf_s("%d", &mode);
		shortestPath(from, to, ht, dt);
		printOutput(dt, from, to, mode);
	}
}

int main(){
	HashTable tab(HASH_TAB_SIZE);
	
	// initialize it once so i wont have to allocate and deallocate memory several times
	DijkstraTable dt(HASH_TAB_SIZE, &tab);

	char** field;
	int w, h;
	List<Pair<int, int>>* citiesPos = new List<Pair<int, int>>;
	field = enterField(w, h, *citiesPos);

	loadGraph(tab, field, *citiesPos, w, h, dt);

	for (int i = 0; i < w; i++)
		delete[] field[i];
	delete[] field;

	delete citiesPos;

	loadFlights(tab);
	handleCommands(tab, dt);
	return 0;
}