#pragma once
#include "Game.h"
#include "GameObject.h"

constexpr auto BRICK_BBOX_WIDTH = 16;
constexpr auto BRICK_BBOX_HEIGHT = 16;

class Brick:public GameObject  
{
public:
	Brick();
	~Brick();

	void render() override;

	// Inherited via GameObject
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

	void update(DWORD dt, vector<GameObject*>* coObjects) override;
};
