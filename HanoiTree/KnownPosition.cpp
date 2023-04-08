#include "KnownPosition.h"

KnownPosition::KnownPosition() {}

KnownPosition::KnownPosition(Position* position, int branchLength) {
	this->position_ = position;
	this->branchLength_ = branchLength;
}

void KnownPosition::setBranchLength(int newLength) {
	this->branchLength_ = newLength;
}

Position* KnownPosition::getPosition() {
	return position_;
}

int KnownPosition::getBranchLength() {
	return branchLength_;
}