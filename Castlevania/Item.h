#pragma once
#include "GameObject.h"
class Item :
	public GameObject
{
public:
	Item();
	~Item();

	void checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks);

	void update(DWORD dt, vector<LPGameObject>* bricks);
	// Inherited via GameObject
	virtual void render() override;
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
};

