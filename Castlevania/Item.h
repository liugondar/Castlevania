#pragma once
#include "GameObject.h"

enum ItemType {
	heartItem = 1,
	whipItem = 2,
	daggerItem=3
};

class Item :
	public GameObject
{
public:
	Item();
	~Item();

	void checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks);
	void update(DWORD dt, vector<LPGameObject>* bricks) override;
	void initAnim() override;
};

