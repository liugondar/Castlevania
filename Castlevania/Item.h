#pragma once
#include "GameObject.h"

enum ItemType {
	heartItem = 1,
	whipItem = 2,
	daggerItem = 3
};

class Item :
	public GameObject
{
protected:
	int itemType;
public:
	Item();
	~Item();

	void checkCollision(DWORD dt, vector<LPGameObject> *bricks);
	void update(DWORD dt, vector<LPGameObject>* coObjects) override;
	void initAnim() override;
	void setItemType(const int type) { itemType = type; }
	int getItemType() const { return itemType; }
};

