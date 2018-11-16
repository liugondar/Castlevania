#pragma once
#include "GameObject.h"
constexpr auto BIG_CANDLE_WIDTH = 32;
constexpr auto BIG_CANDLE_HEIGHT= 64;
constexpr auto BIG_CANDLE_ANIMATION_FRAME_TIME = 100;

enum ItemBigCandleContain
{
	heart=1,
	dagger=2,
	whipUpgrade=3
};

class BigCandle :
	public GameObject
{
	int itemContain;
public:
	BigCandle();
	~BigCandle();

	// Inherited via GameObject
	virtual void render() override;
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void setItemContain(int item);
};

