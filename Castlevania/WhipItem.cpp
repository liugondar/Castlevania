#include "WhipItem.h"
#include "StageManager.h"

WhipItem::WhipItem(): Item()
{
	itemType = ItemType::whipItem;
}

void WhipItem::update(DWORD dt, vector<LPGameObject>* bricks)
{
	Item::update(dt, bricks);
}

void WhipItem::render()
{
	if (currentState != State::dead)animations[ANIM_WHIP_ITEM_IDLE]->render(x, y);
	else
	{
		StageManager::getInstance()->remove(this);
	}
}

void WhipItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + WHIP_ITEM_W;
	bottom = y + WHIP_ITEM_H;
}

