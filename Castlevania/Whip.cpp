#include "Whip.h"



Whip::Whip()
{
	lv = 1;
	animationId = -1;
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
	if (lv == 3)
	{
		animationId = faceSide == FaceSide::left
			? ANIM_WHIP_LV3_L
			: ANIM_WHIP_LV3_R;
	}
	else if (lv == 2)
	{
		animationId = faceSide == FaceSide::left
			? ANIM_WHIP_LV2_L
			: ANIM_WHIP_LV2_R;
	}
	else
	{
		animationId = faceSide == FaceSide::left
			? ANIM_WHIP_LV1_L
			: ANIM_WHIP_LV1_R;
	}

	animations[animationId]->render(x, y, true);

	const auto frame = animations[animationId]->getFrame();

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

void Whip::setSide(int side)
{
	faceSide = side;
}

void Whip::refreshAnim()
{
	//if(animations[ANIM_WHIP_LV1_L])animations[ANIM_WHIP_LV1_L]->refresh();
	//if(animations[ANIM_WHIP_LV1_L])animations[ANIM_WHIP_LV1_R]->refresh();
	//if(animations[ANIM_WHIP_LV2_L])animations[ANIM_WHIP_LV2_L]->refresh();
	//if(animations[ANIM_WHIP_LV2_L])animations[ANIM_WHIP_LV2_R]->refresh();

	if (animations[animationId]) animations[animationId]->refresh();
}


void Whip::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == STATE_WHIP_HITTING) {
		if (faceSide == FaceSide::left) {
			if (lv == 1) left = x - WHIP_LV1_HITTING_W;
			else if (lv == 2) left = x - WHIP_LV2_HITTING_W;
			else if (lv == 3) left = x - WHIP_LV3_HITTING_W;
			else left = 0;

			right = x + 5;
			top = y + 16;
		}
		else {
			left = x + SIM_HIT_W - 5;
			if (lv == 1) right = x + SIM_HIT_W + WHIP_LV1_HITTING_W - 5;
			else if (lv == 2) right = x + SIM_HIT_W + WHIP_LV2_HITTING_W - 5;
			else if (lv == 3) right = x + SIM_HIT_W + WHIP_LV3_HITTING_W - 5;
			else right = 0;
		}

		top = y + 20;
		bottom = top + WHIP_LV1_HITTING_H;
	}
	else {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Whip::upgradeWhipLv()
{
	if (lv < MAX_WHIP_LV) lv++;
}