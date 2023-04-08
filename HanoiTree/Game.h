#pragma once
#include "Stack.h"
#include "Position.h"


class Game {
public:
	std::vector<Stack> stacks;
	std::vector<Stack> stacksPointers;
	int startingStackIndex, targetStackIndex, numberOfStacks, numberOfCubes;

	Game(int numberOfStacks, int startingStackIndex, int targetStackIndex, int numberOfCubes);

	void initialiseCubes();
};