#include "Animation.h"

void Animation::add(int spriteId, DWORD time) {
	int t = time;
	if (time == 0) t = this->defaultTime;
	auto spriteManager = SpriteManager::getInstance();
	auto sprite = spriteManager->get(spriteId);
	auto frame = new AnimationFrame(sprite, t);

	frames.push_back(frame);
}

void Animation::render(float x, float y) {
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
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}

	frames[currentFrame]->getSprite()->draw(x, y);
}