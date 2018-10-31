#include "Brick.h"


Brick::Brick()
{
}


Brick::~Brick()
{
}

void Brick::render()
{
	RenderBoundingBox();
	animations[ANIMATION_BRICK_IDLE]->render(x, y);
}

Box Brick::getBoundingBox()
{
	auto box = Box();
	box.left = x;
	box.top = y;
	box.right = x + BRICK_BBOX_WIDTH;
	box.bottom = y + BRICK_BBOX_HEIGHT;
	return box;
}
