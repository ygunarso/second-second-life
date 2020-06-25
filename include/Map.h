#pragma once

#include "Game.h"
#include <fstream>

using namespace std;

class Map {
public:
	Map();

	~Map();

	static void loadMap(string path, int column, int row);

private:

};