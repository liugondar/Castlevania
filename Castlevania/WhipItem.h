#pragma once
#include "Item.h"

constexpr auto WHIP_ITEM_W = 32;
constexpr auto WHIP_ITEM_H = 32;


class WhipItem :
	public Item
{
public:
	WhipItem();
	~WhipItem();
	void update(DWORD dt, vector<LPGameObject>* bricks) override;
	void render() override;
	void getBoundingBox(float& left, float& top, float& right, float& bottom) override;
};

