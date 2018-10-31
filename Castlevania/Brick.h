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

	// Inherited via GameObject
	virtual Box getBoundingBox() ;
	void render() ;
};

