#pragma once
#include "AnimationFrame.h"
#include "SpriteManager.h"
#include "Constants.h"
using namespace std;

enum AnimState
{
	rendered = 1,
	notRenderedYet = -1
};

class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	bool isRendered;
	int state = -1;
	vector <AnimationFrame* > frames;
	bool isOneTimeAnim;
public:
	Animation(int defaultTime) {
		this->defaultTime = defaultTime;
		lastFrameTime = -1;
		currentFrame = -1;
		state = -1;
	}

	int getFrame();
	void add(int spriteId, DWORD time = 0);
	void render(float x, float y);
	void refresh();
	bool isDone();
	void setIsOneTimeAnim(bool isOnetimeAnim);
};
