#pragma once
#include "Cube.h"
#include <ostream>
#include <vector>

class Stack {
public:
	int index;
	std::vector<Cube*> cubesPointers;
	void pushBack(Cube& cube);
	void pushBackPointer(Cube* cube);
	Cube removeTop();
	Cube& popBack();
	unsigned size() const;

	friend std::ostream& operator<<(std::ostream& os, const Stack& stack);

	Stack();
	Stack(int i);

	std::vector<Cube> getCubes();

private:
	std::vector<Cube> _cubes;
};
