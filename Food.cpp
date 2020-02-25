#include "pch.h"
#include "Food.h"
#include "Snake.h"
#include "Map.h"

Food::Food() {
	count = 4;
	step = 30;
	srand((unsigned)time(NULL));
}

void Food::generate_new_food(Snake* s) {
	count++;
	if (count % 6 == 0) {
		type = BIG;
	}
	else type = SMALL;
	int X = rand() % MAP_SIZE;
	int Y = rand() % MAP_SIZE;
	while (s->in_snake(X, Y)) {
		X = rand() % MAP_SIZE;
		Y = rand() % MAP_SIZE;
	}
	y = X;
	x = Y;
}

void Food::display(CPaintDC *dc) {
	if (type == SMALL) {
		CBrush food_brush(RGB(167, 224, 230));
		dc->SelectObject(&food_brush);
		int X = WALL_WIDTH + x * CELL_SIZE;
		int Y = WALL_WIDTH + y * CELL_SIZE;
		dc->Ellipse(X + CELL_SIZE / 4, Y + CELL_SIZE / 4, X + 3 * CELL_SIZE / 4, Y + 3 * CELL_SIZE / 4);
	}
	else if (type == BIG) {
		CBrush food_brush(RGB(255, 0, 0));
		dc->SelectObject(&food_brush);
		int X = WALL_WIDTH + x * CELL_SIZE;
		int Y = WALL_WIDTH + y * CELL_SIZE;
		dc->Ellipse(X, Y, X + CELL_SIZE, Y + CELL_SIZE);
	}

}

