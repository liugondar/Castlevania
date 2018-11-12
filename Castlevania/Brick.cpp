#include "Brick.h"


Brick::Brick()
{
}


Brick::~Brick()
{
}

void Brick::render()
{
	animations[ANIMATION_BRICK_IDLE]->render(x, y);
}

void Brick::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BRICK_2_SIZE;
	bottom = y + BRICK_2_SIZE;
}

