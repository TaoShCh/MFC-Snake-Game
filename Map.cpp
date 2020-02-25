#include "pch.h"
#include "Map.h"

Map::Map() {
	x = y = MAP_SIZE;
	map = new int* [MAP_SIZE];
	for (int i = 0; i < MAP_SIZE; i++) {
		map[i] = new int[MAP_SIZE];
		for (int j = 0; j < MAP_SIZE; j++) {
			map[i][j] = SPACE;
		}
	}

}

Map::Map(int X, int Y) {
	x = X;
	y = Y;
	map = new int* [Y];
	for (int i = 0; i < Y; i++) {
		map[i] = new int[X];
	}
}

void Map::set_map(int** Template) {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			map[i][j] = Template[i][j];
		}
	}
}

int Map::get_point(int x, int y) {
	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE) {
		return WALL;
	}
	return map[y][x];
}
