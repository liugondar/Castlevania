#include "KnifeItem.h"
#include "GameObjectManger.h"
#include "WhipItem.h"


KnifeItem::KnifeItem()
{
}


KnifeItem::~KnifeItem()
{
}

void KnifeItem::render()
{
	if (currentState != State::dead)animations[ANIM_KNIFE_ITEM_IDLE]->render(x, y, true);
	else
	{
		GameObjectManger::getInstance()->removeItem(this);
	}
}

void KnifeItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KNIFE_ITEM_W;
	bottom = y + KNIFE_ITEM_H;
}

void KnifeItem::update(DWORD dt, vector<LPGameObject>* bricks)
{
	Item::update(dt, bricks);
}
