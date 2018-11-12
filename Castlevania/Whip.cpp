#include "Whip.h"



Whip::Whip()
{
}


Whip::~Whip()
{
}

void Whip::checkEnemyCollisions(vector<LPGameObject> coObjects)
{
	for (int i = 0; i < coObjects.size(); i++)
	{
		float bl, bt, br, bb;
		float sl, st, sr, sb;


		coObjects[i]->getBoundingBox(sl, st, sr, sb);
		getBoundingBox(bl, bt, br, bb);
		if (isColliding(bl, bt, br, bb, sl, st, sr, sb)) {
			coObjects[i]->setState(-1);
		}
	}
}

void Whip::render()
{
	animationId = faceSide == FaceSide::left
		? ANIMATION_WHIP_LV1_LEFT
		: ANIMATION_WHIP_LV1_RIGHT;

	animations[animationId]->render(x, y,true);

	auto frame = animations[animationId]->getFrame();

	if (frame == 0) setState(STATE_WHIP_READY_HIT);
	else if (frame == 1) setState(STATE_WHIP_START_HIT);
	else if (frame == 2) setState(STATE_WHIP_HITTING);
	else setState(STATE_WHIP_DISAPPEAR);
}


void Whip::update(DWORD dt, float x, float y, vector<LPGameObject> *coObject)
{
	GameObject::update(dt);
	setPosition(x, y);

	auto state = getState();
	if (state == STATE_WHIP_HITTING) {
		checkEnemyCollisions(*coObject);
	}
}

void Whip::setSide(FaceSide side)
{
	faceSide = side;
}

void Whip::refreshAnim()
{
	animations[ANIMATION_WHIP_LV1_LEFT]->refresh();
	animations[ANIMATION_WHIP_LV1_RIGHT]->refresh();
}


void Whip::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == STATE_WHIP_HITTING) {
		auto width = x;
		auto height = y;

		if (faceSide == FaceSide::left) {
			left = x - WHIP_HITTING_WIDTH;
			right = x + 10;
		}
		else {
			left = x + SIMON_HITTING_WIDTH - 10;
			right = left + WHIP_HITTING_WIDTH;
		}
		top = y + 13;
		bottom = top + WHIP_HITTING_HEIGHT;
	}
	else {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}
