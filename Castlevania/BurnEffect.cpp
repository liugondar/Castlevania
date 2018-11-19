#include "BurnEffect.h"
#include "GameObjectManger.h"


BurnEffect::BurnEffect()
{
	BurnEffect::initAnim();
}


BurnEffect::~BurnEffect()
= default;


void BurnEffect::render()
{
	if (animations[ANIM_BURN_EFFECT]) {
		if (animations[ANIM_BURN_EFFECT]->isDone())
		{
			GameObjectManger::getInstance()->removeGameObject(this);
		}
		animations[ANIM_BURN_EFFECT]->render(x, y);
	}
}

void BurnEffect::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = 0;
	bottom = 0;
}


void BurnEffect::update(DWORD dt, vector<GameObject*>* coObjects)
{
}

void BurnEffect::initAnim()
{
	addAnimation(ANIM_BURN_EFFECT);
	animations[ANIM_BURN_EFFECT]->refresh();
}
