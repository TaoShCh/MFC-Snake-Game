#include "pch.h"
#include "Snake.h"
#include "Map.h"
#include "Food.h"
Snake::Snake() {
	length = 4;
	body[0] = { 2,5 };
	body[1] = { 2,4 };
	body[2] = { 2,3 };
	body[3] = { 2,2 };
	direction = DOWN;
}

void Snake::move_down() {
	for (int i = length - 1; i > 0; i--) {
		body[i] = body[i - 1];
	}
	body[0].y++;
}

void Snake::move_up() {
	for (int i = length - 1; i > 0; i--) {
		body[i] = body[i - 1];
	}
	body[0].y--;
}

void Snake::move_left() {
	for (int i = length - 1; i > 0; i--) {
		body[i] = body[i - 1];
	}
	body[0].x--;
}

void Snake::move_right() {
	for (int i = length - 1; i > 0; i--) {
		body[i] = body[i - 1];
	}
	body[0].x++;
}

void Snake::move() {
	switch (direction) {
	case LEFT:
		move_left();
		break;
	case RIGHT:
		move_right();
		break;
	case UP:
		move_up();
		break;
	case DOWN:
		move_down();
		break;
	default:
		break;
	}
}

void Snake::change_direction(char input) {
	switch (input)
	{
	case VK_UP:
		if (direction != DOWN)
			direction = UP;
		break;
	case VK_LEFT:
		if (direction != RIGHT)
			direction = LEFT;
		break;
	case VK_DOWN:
		if (direction != UP)
			direction = DOWN;
		break;
	case VK_RIGHT:
		if (direction != LEFT)
			direction = RIGHT;
		break;
	default: break;
	}
}

void Snake::display(CPaintDC *dc) {
	CBrush snake_body(RGB(0, 0, 0));
	dc->SelectObject(&snake_body);
	CPoint head[4];
	head[0].x = WALL_WIDTH + body[0].x * CELL_SIZE + CELL_SIZE / 2;
	head[0].y = WALL_WIDTH + body[0].y * CELL_SIZE;
	head[1].x = WALL_WIDTH + body[0].x * CELL_SIZE + CELL_SIZE;
	head[1].y = WALL_WIDTH + body[0].y * CELL_SIZE + CELL_SIZE / 2;
	head[2].x = WALL_WIDTH + body[0].x * CELL_SIZE + CELL_SIZE / 2;
	head[2].y = WALL_WIDTH + body[0].y * CELL_SIZE + CELL_SIZE;
	head[3].x = WALL_WIDTH + body[0].x * CELL_SIZE;
	head[3].y = WALL_WIDTH + body[0].y * CELL_SIZE + CELL_SIZE / 2;
	dc->Polygon(head, 4);
	for (int i = 1; i < length; i++) {
		int x = WALL_WIDTH + body[i].x * CELL_SIZE;
		int y = WALL_WIDTH + body[i].y * CELL_SIZE;
		dc->Ellipse(x, y, x + CELL_SIZE, y + CELL_SIZE);
	}
}

bool Snake::in_snake(int y, int x) {
	for (int i = 0; i < length; i++) {
		if (body[i].y == y && body[i].x == x) {
			return 1;
		}
	}
	return 0;
}

void Snake::length_increase(Map *m) {
	int x = 2 * body[length - 1].x - body[length - 2].x;
	int y = 2 * body[length - 1].y - body[length - 2].y;
	if (in_snake(y, x) || m->get_point(y, x) == WALL) {
		x = body[length - 1].x;
		y = body[length - 1].y + 1;
	}
	if (in_snake(y, x) || m->get_point(y, x) == WALL) {
		x = body[length - 1].x;
		y = body[length - 1].y - 1;
	}
	if (in_snake(y, x) || m->get_point(y, x) == WALL) {
		x = body[length - 1].x + 1;
		y = body[length - 1].y;
	}
	if (in_snake(y, x) || m->get_point(y, x) == WALL) {
		x = body[length - 1].x - 1;
		y = body[length - 1].y;
	}
	body[length].y = y;
	body[length].x = x;
	length++;
}

bool Snake::hit_itself() {
	for (int i = 1; i < length; i++) {
		if (body[i].y == body[0].y && body[i].x == body[0].x) {
			return 1;
		}
	}
	return 0;
}

bool Snake::eat_food(Food* f) {
	if (body[0].x == f->x && body[0].y == f->y)
		return 1;
	else return 0;
}

bool Snake::hit_wall(Map* m) {
	if (m->get_point(body[0].x, body[0].y) == WALL) {
		return 1;
	}
	else return 0;
}