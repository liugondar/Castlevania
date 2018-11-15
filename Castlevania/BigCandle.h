#pragma once
#include "GameObject.h"
#include "GameObjectManger.h"
constexpr auto BIG_CANDLE_WIDTH = 32;
constexpr auto BIG_CANDLE_HEIGHT= 64;
constexpr auto BIG_CANDLE_ANIMATION_FRAME_TIME = 100;


class BigCandle :
	public GameObject
{
public:
	BigCandle();
	~BigCandle();

	// Inherited via GameObject
	virtual void render() override;
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
};

