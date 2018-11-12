#pragma once
#include "AnimationFrame.h"
#include "SpriteManager.h"
#include "Constants.h"
using namespace std;

enum AnimationState{
	done = 1, acting = 0, notRender = 3
};

class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	bool isRendered;
	int state=-1;
	vector <AnimationFrame* > frames;
public:
	Animation(int defaultTime) {
		this->defaultTime = defaultTime;
		lastFrameTime = -1;
		currentFrame = -1;
		state = -1;
	}
	int getFrame() { return currentFrame; }
	void add(int spriteId, DWORD time = 0);
	void render(float x, float y,bool isOneTimeAnim=false);
	void refresh();
	bool isDone();
};
