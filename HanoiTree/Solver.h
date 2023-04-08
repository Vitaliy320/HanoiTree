#pragma once
#include "Stack.h"
#include "Cube.h"
#include "Position.h"
#include <string>
#include "knownPosition.h"

class Solver {
public:
	Position* positionsTree;
	int numberOfStacks, startingStackIndex, targetStackIndex, numberOfCubes, minBranchLength;
	Position startingPosition, currentPosition;

	Solver(int numberOfStacks, int startingStackIndex, int targetStackIndex, int numberOfCubes, Position& position);

	Position* getTree();
	Position* getSolutionsDepth(Position* currentPosition, int* index);
	Position* getSolutionsBreadth(std::vector<Position*> currentLayer, int* index);

	Stack getStackByIndexValue(std::vector<Stack> stacks, int index);

	bool positionInVectorOfPositions(Position* position);
	bool equalPositions(Position position1, Position position2);

	int getBranchLength(Position* position);

	void removeBranchUpToRoot(Position* position);

	std::vector<KnownPosition> knownPositions;

	bool currentPositionHasLongerBranchLength(Position* position, KnownPosition* knownPosition);

	void printBranch(Position* position);

	std::vector<Position*> finalPositions;

	Position* createPositionFromInitialStack(Stack stack, Position* currentPosition);

private:
	std::vector<Stack> getRemainingStacks(std::vector<Stack> stacksToFilter, Stack stackToExclude);
	bool _compareVectorsOfCubes(std::vector<Cube> vector1, std::vector<Cube> vector2);
	bool _stackInVectorOfStacks(std::vector<Stack> knownStacks, Stack positionStack);
	void _printInfo(Position currentPosition);
	Position* _getRootPosition(Position* position);
	void _bfs(std::vector<Position*> positionsLayer);
};