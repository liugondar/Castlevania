#include "BigCandle.h"



BigCandle::BigCandle()
{
}


BigCandle::~BigCandle()
{
}

void BigCandle::render()
{
	if(getState()!=-1)animations[ANIMATION_BIG_CANDLE_IDLE]->render(x, y);
}



void BigCandle::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BIG_CANDLE_WIDTH;
	bottom = y + BIG_CANDLE_HEIGHT;
}
