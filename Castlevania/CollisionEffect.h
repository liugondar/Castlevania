#pragma once
#include "GameObject.h"

class CollisionEffect: public GameObject
{
public:
	CollisionEffect();
	~CollisionEffect();
	void render() override;
	void getBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void initAnim() override;
};

