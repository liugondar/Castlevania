#include "BigCandle.h"
#include "HeartItem.h"
#include "GameObjectManger.h"
#include "WhipItem.h"
#include "KnifeItem.h"

BigCandle::BigCandle()
{
}


BigCandle::~BigCandle()
{
}

void BigCandle::render()
{
	if (currentState != State::dead) animations[ANIMATION_BIG_CANDLE_IDLE]->render(x, y);
	else {
		auto gameObjectManger = GameObjectManger::getInstance();
		Item * item = nullptr;
		if (id == BIG_CANDLE1_ID) {
			item = new HeartItem();
			item->setType(ItemType::heart);
		}
		else if (id == BIG_CANDLE2_ID) {
			item = new WhipItem();
			item->setType(ItemType::whip);
		}
		else if(id== BIG_CANDLE3_ID)
		{
			item = new KnifeItem();
			item->setType(ItemType::knife);
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
