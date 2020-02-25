#include "common.h"
class Map;
class Food;
struct Node {
	int x, y;
};

class Snake
{
private:
	Node body[MAX_LENGTH];
	int length;
	int direction;
	void move_right();
	void move_left();
	void move_up();
	void move_down();
public:
	Snake();
	void move();
	void display(CPaintDC *dc);
	void change_direction(char input);
	bool hit_wall(Map* m);
	bool hit_itself();
	bool in_snake(int h, int w);
	bool eat_food(Food* f);
	void length_increase(Map *m);
};

