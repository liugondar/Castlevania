#pragma once
#include "GameObject.h"

enum ItemType {
	heart = 1,
	whip = 2,
	knife=3
};

class Item :
	public GameObject
{
public:
	Item();
	~Item();

	void checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks);

	void update(DWORD dt, vector<LPGameObject>* bricks) override;
	virtual void render()=0;
	virtual void getBoundingBox(float& left, float& top, float& right, float& bottom)=0;
	// Inherited via GameObject
};

