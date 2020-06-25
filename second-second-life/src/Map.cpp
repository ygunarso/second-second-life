#include "Map.h"

Map::Map() {

}

Map::~Map() {

}

void Map::loadMap(string path, int col, int row) {
	char tile;
	fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < row; y++) {
		for (int x = 0; x < col; x++) {
			mapFile.get(tile);
			Game::addTile(atoi(&tile), x * 64, y * 64);
			mapFile.ignore();
		}
	}

	mapFile.close();
}