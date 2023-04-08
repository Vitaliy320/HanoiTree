#pragma once
#include <vector>
#include "Stack.h"
#include <iostream>

class Position {
public:
	Position();
	Position(std::vector<Stack>& position);

	void getParentNode();
	void addNode(Position* position);
	void setPosition(std::vector<Stack> position);
	std::vector<Stack> getPositionStacks();
	Position* getParentPointer();
	std::vector<Position*> getChildPointers();
	void setParentPointer(Position* parent);
	void setChildPointers(Position* child);
	bool isFinal;
	int index;

private:
	Position* _parentPointer;
	std::vector<Position*> _childPointers;
	std::vector<Stack> _positionStacks;
};