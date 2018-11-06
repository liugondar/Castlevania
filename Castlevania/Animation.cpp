#include "Animation.h"

void Animation::add(int spriteId, DWORD time) {
	int t = time;
	if (time == 0) t = this->defaultTime;
	auto spriteManager = SpriteManager::getInstance();
	auto sprite = spriteManager->get(spriteId);
	auto frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::render(float x, float y,bool isOneTimeAnim) {
	auto now = GetTickCount();
	if (currentFrame == -1) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	else {
		auto t = frames[currentFrame]->getTime();
		if (now - lastFrameTime > t) {
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				if (isOneTimeAnim ) {
					currentFrame = currentFrame - 1;
					state =1;
				}
					else currentFrame = 0;
			}
		}
	}
	frames[currentFrame]->getSprite()->draw(x, y);
}

bool Animation::isDone()
{
	if (state == 1) return true;
	return false;
}

void Animation::refresh()
{
	currentFrame = -1;
	state = -1;
}
