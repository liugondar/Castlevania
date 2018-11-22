#pragma once
#include "Item.h"

class HeartItem: public Item
{
public:
	HeartItem();;
	~HeartItem();
	void update(DWORD dt, vector<LPGameObject>* bricks) override;
	void render() override;
	void getBoundingBox(float& left, float& top, float& right, float& bottom) override;
};

