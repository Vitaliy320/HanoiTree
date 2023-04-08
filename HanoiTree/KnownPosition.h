#pragma once
#include "Position.h"
#include <vector>

class KnownPosition {
public:
	KnownPosition();
	KnownPosition(Position* position, int branchLength);

	void setBranchLength(int newLength);

	Position* getPosition();
	int getBranchLength();

private:
	Position* position_;
	int branchLength_;
};
