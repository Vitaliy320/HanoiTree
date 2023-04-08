#include "Position.h"

Position::Position() {
	_parentPointer = nullptr;
	isFinal = false;
}

Position::Position(std::vector<Stack>& position) {
	_positionStacks = position;
	_parentPointer = nullptr;
	//childPointers_ = std::vector<Position*>;
	isFinal = false;
}

void Position::setPosition(std::vector<Stack> position) {
	_positionStacks = position;
}

std::vector<Stack> Position::getPositionStacks() {
	return _positionStacks;
}

Position* Position::getParentPointer() {
	return _parentPointer;
}

std::vector<Position*> Position::getChildPointers() {
	return _childPointers;
}

void Position::setParentPointer(Position* parent) {
	_parentPointer = parent;
}

void Position::setChildPointers(Position* child) {
	_childPointers.push_back(child);
}

void Position::addNode(Position* position) {
	Position* node = this;
	/*while (node->getChildPointers() != nullptr) {
		node = node->getChildPointers();
	}
	position->setParentPointer(node);
	node->setChildPointers(position);*/
}