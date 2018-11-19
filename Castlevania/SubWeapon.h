#pragma once
#include "GameObject.h"

enum SubWeaponState
{
	active=1,
	inActive=-1
};

class SubWeapon : public GameObject
{
	float cameraX, cameraY;
public:
	SubWeapon();
	~SubWeapon();
	void setSide(int side)
	{
		faceSide = side;
	}
	virtual void update(DWORD dt, vector<GameObject*>* coObjects) override = 0;
	virtual void render() override = 0;
	virtual void getBoundingBox(float& left, float& top, float& right, float& bottom) override = 0;
};

