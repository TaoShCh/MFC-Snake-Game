#pragma once
#include "common.h"

class Map
{
private:
	int x, y;
	int** map;

public:
	Map();
	Map(int X, int Y);
	void set_map(int** Template);
	int get_point(int x, int y);
};
