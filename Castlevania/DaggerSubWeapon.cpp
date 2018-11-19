#include "DaggerSubWeapon.h"



DaggerSubWeapon::DaggerSubWeapon()
{
	vx = DAGGER_VX;
	faceSide = FaceSide::right;
}


DaggerSubWeapon::~DaggerSubWeapon()
{
}

void DaggerSubWeapon::checkEnemyCollisions(vector<LPGameObject>* coObjects)
{
	/*vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();

	calcPotentialCollisions(coObjects, coEvents);

	if (!coEvents.empty()) {
		float minTx, minTy, nx = 0, ny;
		filterCollision(coEvents, coEventsResult, minTx, minTy, nx, ny);
		for (auto& i : coEventsResult)
		{
			const auto item = i->obj;
			item->setState(-1);
		}
	}

	for (auto& coEvent : coEvents) delete coEvent;*/

	for (auto& coObject : *coObjects)
	{
		float bl, bt, br, bb;
		float sl, st, sr, sb;
		coObject->getBoundingBox(sl, st, sr, sb);
		getBoundingBox(bl, bt, br, bb);
		if (isColliding(bl, bt, br, bb, sl, st, sr, sb)) {
			coObject->setState(-1);
		}
	}
}

void DaggerSubWeapon::render()
{
	float camX, camY;
	Game::getInstance()->getCameraPosition(camX, camY);
	if (x<camX - DAGGER_W || x>camX + SCREEN_WIDTH ) setState(SubWeaponState::inActive);
	if (currentState == SubWeaponState::inActive) return;
	animationId = faceSide == FaceSide::left ?
		ANIM_DAGGER_L : ANIM_DAGGER_R;
	animations[animationId]->render(x, y);
}

void DaggerSubWeapon::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_W;
	bottom = y + DAGGER_H;
}

void DaggerSubWeapon::update(const DWORD dt, vector<GameObject*>* coObjects)
{
	GameObject::update(dt);
	if (currentState == inActive) return;
	vx = faceSide == FaceSide::left ? -DAGGER_VX : DAGGER_VX;
	x += dx;
	checkEnemyCollisions(coObjects);
}
