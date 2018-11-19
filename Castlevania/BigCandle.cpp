#include "BigCandle.h"
#include "HeartItem.h"
#include "GameObjectManger.h"
#include "WhipItem.h"
#include "DaggerItem.h"
#include <stdlib.h>

BigCandle::BigCandle()
{
	itemContain = -1;
	initAnim();
}


BigCandle::~BigCandle()
{
}

void BigCandle::render()
{
	if (currentState != State::dead) animations[ANIM_BIG_CANDLE_IDLE]->render(x, y);
	else {
		auto gameObjectManger = GameObjectManger::getInstance();
		Item * item = nullptr;
		if (itemContain == -1)
		{
			itemContain = rand() % 3 + 1;
			DebugOut(L"item %d\n", itemContain);
		}
		if (itemContain == ItemBigCandleContain::heart) {
			item = new HeartItem();
			item->setType(ItemType::heartItem);
		}
		else if (itemContain == ItemBigCandleContain::whipUpgrade) {
			item = new WhipItem();
			item->setType(ItemType::whipItem);
		}
		else if (itemContain == ItemBigCandleContain::dagger)
		{
			item = new DaggerItem();
			item->setType(ItemType::daggerItem);
		}

		if (item) {
			item->setPosition(x, y);
			gameObjectManger->addItem(item);
		}
		gameObjectManger->removeGameObject(this);
	}
}



void BigCandle::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BIG_CANDLE_WIDTH;
	bottom = y + BIG_CANDLE_HEIGHT;
}

void BigCandle::setItemContain(int item)
{
	itemContain = item;
}

void BigCandle::initAnim()
{
	addAnimation(ANIM_BIG_CANDLE_IDLE);
}
