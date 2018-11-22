#include "Brick.h"


Brick::Brick()
{
	type = GameObjectType::brick;
	initAnim();
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

void Brick::update(DWORD dt, vector<GameObject*>* coObjects)
{
}

void Brick::initAnim()
{
	addAnimation(ANIMATION_BRICK_IDLE);
}
