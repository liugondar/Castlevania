#include "CollisionEffect.h"
#include "GameObjectManger.h"


CollisionEffect::CollisionEffect()
{
	CollisionEffect::initAnim();
}


CollisionEffect::~CollisionEffect()
= default;

void CollisionEffect::render()
{
	if (animations[ANIM_COLLISION_EFFECT]) {
		auto frame = animations[ANIM_COLLISION_EFFECT]->getFrame();
		if (animations[ANIM_COLLISION_EFFECT]->isDone()) {
			GameObjectManger::getInstance()->removeGameObject(this);
		}
		animations[ANIM_COLLISION_EFFECT]->render(x, y);
	}
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
	animations[ANIM_COLLISION_EFFECT]->refresh();
}
