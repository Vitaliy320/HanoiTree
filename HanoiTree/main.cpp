#include <iostream>
#include "Cube.h"
#include <stdlib.h>
#include <time.h>
#include <random>
#include <math.h>
#include "Game.h"

using namespace std;

int main() {
	Game game = Game(3, 0, 2, 4);
	game.initialiseCubes();

	return 0;
}