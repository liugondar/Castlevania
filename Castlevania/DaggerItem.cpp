#include "DaggerItem.h"
#include "GameObjectManger.h"
#include "WhipItem.h"


DaggerItem::DaggerItem()
{
}


DaggerItem::~DaggerItem()
{
}

void DaggerItem::render()
{
	if (currentState != State::dead)animations[ANIM_KNIFE_ITEM_IDLE]->render(x, y, true);
	else
	{
		GameObjectManger::getInstance()->removeItem(this);
	}
}

void DaggerItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KNIFE_ITEM_W;
	bottom = y + KNIFE_ITEM_H;
}

void DaggerItem::update(DWORD dt, vector<LPGameObject>* bricks)
{
	Item::update(dt, bricks);
}
