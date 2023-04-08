#include "Solver.h"
#include "Position.h"

Solver::Solver(int numberOfStacks, int startingStackIndex, int targetStackIndex, int numberOfCubes, Position& position) {
	this->numberOfStacks = numberOfStacks;
	this->startingStackIndex = startingStackIndex;
	this->targetStackIndex = targetStackIndex;
	this->startingPosition = position;
	this->numberOfCubes = numberOfCubes;
	this->currentPosition = position;
	this->minBranchLength = 0;
}

bool Solver::_compareVectorsOfCubes(std::vector<Cube> vector1, std::vector<Cube> vector2) {
	if (vector1.size() != vector2.size()) {
		return false;
	}

	for (int i = 0; i < vector1.size(); i++) {
		if (!vector1[i].compareWithCube(vector2[i])) {
			return false;
		}
	}
	return true;
}

std::vector<Stack> Solver::getRemainingStacks(std::vector<Stack> stacksToFilter, Stack stackToExclude) {
	std::vector<Stack> possibleStacks;

	for (Stack stack : stacksToFilter) {
		if (stack.index != stackToExclude.index) {
			possibleStacks.push_back(stack);
		}
	}
	return possibleStacks;
}

bool Solver::_stackInVectorOfStacks(std::vector<Stack> knownStacks, Stack positionStack) {
	for (Stack knownStack : knownStacks) {
		if (_compareVectorsOfCubes(knownStack.getCubes(), positionStack.getCubes()) && knownStack.index == positionStack.index) {
			return true;
		}
	}
	return false;
}

bool Solver::equalPositions(Position position1, Position position2) {
	std::vector<Stack> stacks1 = position1.getPositionStacks();
	std::vector<Stack> stacks2 = position2.getPositionStacks();
	Stack stack1;
	Stack stack2;
	int equalStacks = 0;

	for (int i = 0; i < numberOfStacks; i++) {
		stack1 = getStackByIndexValue(stacks1, i);
		stack2 = getStackByIndexValue(stacks2, i);
		if (_compareVectorsOfCubes(stack1.getCubes(), stack2.getCubes())) {
			equalStacks++;
		}
	}
	return equalStacks == numberOfStacks;
}

bool Solver::currentPositionHasLongerBranchLength(Position* position, KnownPosition* knownPosition) {
	int currentBranchLength = getBranchLength(position);

	if (position->getParentPointer() == NULL || currentBranchLength > knownPosition->getBranchLength()) {
		return true;
	}

	knownPosition->setBranchLength(currentBranchLength);
	return false;
}

bool Solver::positionInVectorOfPositions(Position* position) {
	Stack stack0 = getStackByIndexValue(position->getPositionStacks(), 0);
	Stack stack2 = getStackByIndexValue(position->getPositionStacks(), 2);

	for (KnownPosition knownPosition : knownPositions) {
		if (equalPositions(*knownPosition.getPosition(), *position) &&
			currentPositionHasLongerBranchLength(position, &knownPosition)) {
			return true;
		}
	}
	return false;
}

Stack Solver::getStackByIndexValue(std::vector<Stack> stacks, int index) {
	if (stacks.size() > index) {
		for (Stack stack : stacks) {
			if (stack.index == index) {
				return stack;
			}
		}
	}

	return Stack();
}

void Solver::_printInfo(Position currentPosition) {
	std::string stackCubes;
	std::cout << "Position: " << std::to_string(currentPosition.index) << "\n";

	if (currentPosition.getParentPointer() != NULL) {
		std::cout << "Parent position: " << std::to_string(currentPosition.getParentPointer()->index) << "\n";
	}

	for (int i = 0; i < numberOfStacks; i++) {
		Stack stack = getStackByIndexValue(currentPosition.getPositionStacks(), i);
		std::cout << "Stack " << std::to_string(i) << " cubes:\n";

		stackCubes = "";
		for (Cube cube : stack.getCubes()) {
			stackCubes = stackCubes + std::to_string(cube.size) + " ";
		}
		std::cout << stackCubes << "\n";
	}
	std::cout << "\n\n";
}

int Solver::getBranchLength(Position* position) {
	int counter = 0;
	while (position->getParentPointer() != NULL) {
		position = position->getParentPointer();
		counter++;
	}

	return counter;
}

void Solver::removeBranchUpToRoot(Position* position) {
	while (Position* toDelete = position) {
		if (position->getParentPointer() == NULL) {
			break;
		}
		position = position->getParentPointer();
		delete toDelete;
	}
}

void Solver::printBranch(Position* position) {
	while (Position* currentPosition = position) {
		_printInfo(*currentPosition);
		position = position->getParentPointer();
	}
}

Position* Solver::createPositionFromInitialStack(Stack stack, Position* currentPosition) {
	std::vector<Stack> possibleStacks;
	Stack initialStack, remainingStack;
	Cube currentCube;
	Position* newPosition = NULL;

	if (stack.getCubes().size() > 0) {
		possibleStacks = getRemainingStacks(currentPosition->getPositionStacks(), stack);

		for (Stack possibleStack : possibleStacks) {
			initialStack = stack;
			if (possibleStack.getCubes().size() == 0 || possibleStack.getCubes().back().size > initialStack.getCubes().back().size) {

				currentCube = initialStack.popBack();
				possibleStack.pushBack(currentCube);
				remainingStack = getRemainingStacks(possibleStacks, possibleStack).back();
				std::vector<Stack> currentStacks = { initialStack, possibleStack, remainingStack };

				newPosition = new Position(currentStacks);
			}
		}
	}
	return newPosition;
}

Position* Solver::_getRootPosition(Position* position) {
	Position* parentPosition = position->getParentPointer();

	while (parentPosition->getParentPointer() != NULL) {
		parentPosition = parentPosition->getParentPointer();
	}

	return parentPosition;
}

void Solver::_bfs(std::vector<Position*> positionsLayer) {
	std::vector<Position*> currentLayer;

	for (Position* currentPosition : positionsLayer) {
		for (Position* childPosition : currentPosition->getChildPointers()) {
			if (childPosition->isFinal) {
				std::cout << std::to_string(childPosition->index);
				return;
			}

			currentLayer.push_back(childPosition);
		}
	}

	if (currentLayer.size() > 0) {
		_bfs(currentLayer);
	}

	return;
}

Position* Solver::getSolutionsDepth(Position* currentPosition, int* index) {
	//_printInfo(*currentPosition);

	if (getStackByIndexValue(currentPosition->getPositionStacks(), targetStackIndex).getCubes().size() == numberOfCubes) {
		currentPosition->isFinal = true;
		int currentPositionLength = getBranchLength(currentPosition);
		if (minBranchLength == 0 || currentPositionLength < minBranchLength) {
			minBranchLength = currentPositionLength;
		}
		finalPositions.push_back(currentPosition);
		return currentPosition;
	}

	std::vector<Stack> possibleStacks;
	Stack remainingStack, initialStack;
	Position* position;
	Cube currentCube;
	for (Stack stack : currentPosition->getPositionStacks()) {
		if (stack.getCubes().size() > 0) {
			possibleStacks = getRemainingStacks(currentPosition->getPositionStacks(), stack);

			for (Stack possibleStack : possibleStacks) {
				initialStack = stack;
				if (possibleStack.getCubes().size() == 0 || possibleStack.getCubes().back().size > initialStack.getCubes().back().size) {

					currentCube = initialStack.popBack();
					possibleStack.pushBack(currentCube);
					remainingStack = getRemainingStacks(possibleStacks, possibleStack).back();
					std::vector<Stack> currentStacks = { initialStack, possibleStack, remainingStack };

					position = new Position(currentStacks);

					*index = *index + 1;
					position->index = *index;

					position->setParentPointer(currentPosition);

					if (positionInVectorOfPositions(position) || (getBranchLength(position) > minBranchLength && minBranchLength > 0 && position->isFinal == false)) {
						delete position;
						break;
					}

					currentPosition->setChildPointers(position);

					knownPositions.push_back(KnownPosition(position, getBranchLength(position)));
				}
			}
		}
	}

	for (Position* position : currentPosition->getChildPointers()) {
		currentPosition = this->getSolutionsDepth(position, index);
	}

	return currentPosition;
}


Position* Solver::getSolutionsBreadth(std::vector<Position*> currentLayer, int* index) {
	std::vector<Position*> newLayer;
	std::vector<Stack> possibleStacks, remainingStacks;
	Stack initialStack, remainingStack;
	Cube currentCube;
	Position* newPosition;

	for (Position* currentPosition : currentLayer) {
		//_printInfo(*currentPosition);
		if (getStackByIndexValue(currentPosition->getPositionStacks(), targetStackIndex).getCubes().size() == numberOfCubes) {
			currentPosition->isFinal = true;
			int currentPositionLength = getBranchLength(currentPosition);
			if (minBranchLength == 0 || currentPositionLength < minBranchLength) {
				minBranchLength = currentPositionLength;
			}
			finalPositions.push_back(currentPosition);

			Position* rootPosition = _getRootPosition(currentPosition);
			return currentPosition;
		}

		for (Stack stack : currentPosition->getPositionStacks()) {
			if (stack.getCubes().size() > 0) {
				possibleStacks = getRemainingStacks(currentPosition->getPositionStacks(), stack);

				for (Stack possibleStack : possibleStacks) {
					initialStack = stack;
					if (possibleStack.getCubes().size() == 0 || possibleStack.getCubes().back().size > initialStack.getCubes().back().size) {

						currentCube = initialStack.popBack();
						possibleStack.pushBack(currentCube);
						remainingStack = getRemainingStacks(possibleStacks, possibleStack).back();
						remainingStacks = getRemainingStacks(possibleStacks, possibleStack);
						std::vector<Stack> currentStacks = { initialStack, possibleStack };
						currentStacks.insert(currentStacks.end(), remainingStacks.begin(), remainingStacks.end());

						newPosition = new Position(currentStacks);

						if (!(positionInVectorOfPositions(newPosition) || (getBranchLength(newPosition) > minBranchLength && minBranchLength > 0 && newPosition->isFinal == false))) {
							newPosition->setParentPointer(currentPosition);

							*index = *index + 1;
							newPosition->index = *index;

							currentPosition->setChildPointers(newPosition);

							knownPositions.push_back(KnownPosition(newPosition, getBranchLength(newPosition)));
							newLayer.push_back(newPosition);
						}
					}
				}
			}
		}
	}

	return getSolutionsBreadth(newLayer, index);

}


Position* Solver::getTree() {
	Position* positionsTree = &startingPosition, * finalPosition, * rootPosition;
	std::vector<Position*> startingLayer = { &startingPosition };

	startingPosition.index = 0;
	int* index = new int(0);
	*index = 0;
	//finalPosition = getSolutionsDepth(&startingPosition, index);
	finalPosition = getSolutionsBreadth(startingLayer, index);
	rootPosition = _getRootPosition(finalPosition);
	_bfs(startingLayer);

	return finalPosition;
}
