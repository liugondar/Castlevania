#include "Item.h"



Item::Item()
{
}


Item::~Item()
{
}

void Item::checkCollisionWithGround(DWORD dt, vector<LPGameObject>* bricks)
{
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();

	calcPotentialCollisions(bricks, coEvents);

	// no collison
	if (coEvents.size() == 0) {
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0) {
			vy = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Item::update(DWORD dt, vector<LPGameObject>* bricks)
{
	GameObject::update(dt);
	checkCollisionWithGround(dt,bricks);
	vy += 0.002f* dt;
}


void Item::render()
{
	animations[ANIM_HEART_ITEM_IDLE]->render(x, y);
}

void Item::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 24;
	bottom = y + 20;
}
