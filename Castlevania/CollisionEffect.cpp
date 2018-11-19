#include "CollisionEffect.h"



CollisionEffect::CollisionEffect()
{
	CollisionEffect::initAnim();
}


CollisionEffect::~CollisionEffect()
= default;

void CollisionEffect::render()
{
	animations[ANIM_COLLISION_EFFECT]->render(x, y);
}

void CollisionEffect::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = 0;
	bottom = 0;
}

void CollisionEffect::initAnim()
{
	addAnimation(ANIM_COLLISION_EFFECT);
}
