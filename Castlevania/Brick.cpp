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

Box Brick::getBoundingBox()
{
	auto box = Box();
	box.left = x;
	box.top = y;
	box.right = x + BRICK_2_SIZE;
	box.bottom = y + BRICK_2_SIZE;
	return box;
}
