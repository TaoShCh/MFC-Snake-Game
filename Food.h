#pragma once
#include "common.h"
#include <stdlib.h>
#include <time.h>
class Food
{
	friend class Snake;
	friend class CMFCSnakeDlg;
private:
	int x, y;
	int count;
	int type;
	int step;
	
public:
	Food();
	void generate_new_food(Snake* s);
	void display(CPaintDC *dc);
};

