#include "Animation.h"

int Animation::getFrame()
{
	return currentFrame;
}

void Animation::add(int spriteId, DWORD time) {
	int t = time;
	if (time == 0) t = this->defaultTime;
	auto spriteManager = SpriteManager::getInstance();
	auto sprite = spriteManager->get(spriteId);
	auto frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::render(float x, float y) {
	const auto now = GetTickCount();
	if (currentFrame == -1) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	else {
		const auto t = frames[currentFrame]->getTime();
		if (now - lastFrameTime > t) {
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				if (!isOneTimeAnim) currentFrame = 0;
				else
				{
					currentFrame = currentFrame - 1;
					state = AnimState::rendered;
				}
			}
		}
	}
	frames[currentFrame]->getSprite()->draw(x, y);
}

bool Animation::isDone()
{
	return currentFrame == frames.size()-1;
}

void Animation::setIsOneTimeAnim(bool isOnetimeAnim)
{
	this->isOneTimeAnim = isOnetimeAnim;
}

void Animation::refresh()
{
	currentFrame = -1;
	state = AnimState::notRenderedYet;
}
