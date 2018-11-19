#include "HeartItem.h"
#include "GameObjectManger.h"


HeartItem::HeartItem()
{
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
	else
	{
		GameObjectManger::getInstance()->removeItem(this);
	}
}

void HeartItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 24;
	bottom = y + 20;
}
