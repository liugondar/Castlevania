#pragma once
#include "AnimationFrame.h"
#include "SpriteManager.h"
using namespace std;
class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector <AnimationFrame* > frames;
public:
	Animation(int defaultTime) {
		this->defaultTime = defaultTime;
		lastFrameTime = -1;
		currentFrame = -1;
	}
	void add(int spriteId, DWORD time = 0);
	void render(float x, float y);
};
