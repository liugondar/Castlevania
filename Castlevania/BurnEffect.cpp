#include "BurnEffect.h"



BurnEffect::BurnEffect()
{
}


BurnEffect::~BurnEffect()
{
}


void BurnEffect::render()
{
	animations[ANIM_BURN_EFFECT]->render(x, y);
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
