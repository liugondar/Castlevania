#pragma once
#include "GameObject.h"

class BurnEffect: public GameObject
{
public:
	BurnEffect();
	~BurnEffect();
	void render() override;
	void getBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void update(DWORD dt, vector<GameObject*>* coObjects) override;
	void initAnim() override;
};

