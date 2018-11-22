#include "DaggerItem.h"
#include "WhipItem.h"
#include "StageManager.h"


DaggerItem::DaggerItem(): Item()
{
	itemType = ItemType::daggerItem;
}

DaggerItem::~DaggerItem()
{
}

void DaggerItem::render()
{
	if (currentState != State::dead)animations[ANIM_DAGGER_ITEM_IDLE]->render(x, y );
	else
	{
		StageManager::getInstance()->remove(this);
	}
}

void DaggerItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_ITEM_W;
	bottom = y + DAGGER_ITEM_H;
}

void DaggerItem::update(DWORD dt, vector<LPGameObject>* bricks)
{
	Item::update(dt, bricks);
}

