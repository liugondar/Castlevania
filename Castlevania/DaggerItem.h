#pragma once
#include "Item.h"

constexpr auto KNIFE_ITEM_W = 32;
constexpr auto KNIFE_ITEM_H = 18;


class DaggerItem :
	public Item
{
public:
	DaggerItem();
	~DaggerItem();
	void render() override;
	void getBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void update(DWORD dt, vector<LPGameObject>* bricks) override;
};

