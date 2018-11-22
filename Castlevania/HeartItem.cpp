#include "HeartItem.h"
#include "StageManager.h"


HeartItem::HeartItem(): Item()
{
	itemType = ItemType::heartItem;
}

HeartItem::~HeartItem()
{
}

void HeartItem::update(DWORD dt, vector<LPGameObject>* bricks)
{
	Item::update(dt, bricks);
}

void HeartItem::render()
{
	if(currentState!=State::dead)animations[ANIM_HEART_ITEM_IDLE]->render(x, y);
	else {
		StageManager::getInstance()->remove(this);
	}
}

void HeartItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 24;
	bottom = y + 20;
}
