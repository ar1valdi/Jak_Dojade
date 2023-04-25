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
String& getCityString(int x, int y, int w, char** field) {
	
	String* name = new String;

	if (x + 1 == w || (x + 1 < w && !isCityChar(field[x + 1][y]))) {

		while ((isdigit(field[x][y]) || isalpha(field[x][y])) && x != -1) {
			x--;
		}

		x += 1;
	}

	while (isdigit(field[x][y]) || isalpha(field[x][y])) {
		*name += field[x][y];
		x++;
	}

	return *name;
}
String& getCityName(int x, int y, int w, int h, char ** field) {
	String *name = new String;

	if (x - 1 >= 0) {

		if (y - 1 >= 0 && isFirstOrLastLetterOfCity(x - 1, y - 1, w, field)) {
			*name = getCityString(x - 1, y - 1, w, field);
		}

		else if (y + 1 >= 0 && isFirstOrLastLetterOfCity(x - 1, y + 1, w, field)) {
			*name = getCityString(x - 1, y + 1, w, field);
		}

		else if (isFirstOrLastLetterOfCity(x - 1, y, w, field)) {
			*name = getCityString(x - 1, y, w, field);
		}

	}

	if (x + 1 < w && name->isEmpty()) {
			
		if (y - 1 >= 0 && isFirstOrLastLetterOfCity(x + 1, y - 1, w, field)) {
			*name = getCityString(x + 1, y - 1, w, field);
		}

		else if (y + 1 >= 0 && isFirstOrLastLetterOfCity(x + 1, y + 1, w, field)) {
			*name = getCityString(x + 1, y + 1, w, field);
		}

		else if (isFirstOrLastLetterOfCity(x + 1, y, w, field)) {
			*name = getCityString(x + 1, y, w, field);
		}

	}

	if (name->isEmpty() && y - 1 >= 0 && isFirstOrLastLetterOfCity(x, y - 1, w, field)) {
		*name = getCityString(x, y - 1, w, field);
	}

	if (name->isEmpty() && y + 1 < h && name->isEmpty()) {
		*name = getCityString(x, y + 1, w, field);
	}

	return *name;
}
bool isInMap(int x, int y, int w, int h) {
	if (x >= 0 && x < w && y >= 0 && y < h)
		return true;
	return false;
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

		for (Pair<int, int> dir : dirs) {
			int checkX = cities[i].getVal().first + dir.first;
			int checkY = cities[i].getVal().secound + dir.secound;

			if (isInMap(checkX, checkY, w, h) && !visitedBoolMap[checkX][checkY]) {

			}
		}

		tmp = tmp->getNext();
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

	tab.print();

	std::cout << '\n';
	std::cout << '\n';
	
	for (int i = 0; i < h; i++) {
		for(int j =0; j < w; j++)
			std::cout << field[j][i];
		std::cout << '\n';
	}
}