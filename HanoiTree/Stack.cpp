#include "Stack.h"
#include <iostream>
using namespace std;

Stack::Stack() {}

Stack::Stack(int i) {
	index = i;
}

void Stack::pushBack(Cube& cube) {
	//cube.size = 0;
	_cubes.push_back(cube);
}

void Stack::pushBackPointer(Cube* cube) {
	cubesPointers.push_back(cube);
	(*cube).size = 0;
}

std::vector<Cube> Stack::getCubes() {
	return _cubes;
}

Cube& Stack::popBack() {
	Cube& topCube = _cubes.back();
	_cubes.pop_back();
	return topCube;
}

