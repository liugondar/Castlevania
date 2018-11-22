#include "Item.h"


Item::Item()
{
	type = GameObjectType::item;
	Item::initAnim();
}


Item::~Item()
{
}

void Item::checkCollision(DWORD dt, vector<LPGameObject>* bricks)
{
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();

	calcPotentialCollisions(bricks, coEvents);

	// no collison
	if (coEvents.empty()) {
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

	for (auto& coEvent : coEvents) delete coEvent;
}

void Item::update(DWORD dt, vector<LPGameObject>* bricks)
{
	GameObject::update(dt);
	checkCollision(dt,bricks);
	vy += 0.002f* dt;
}

void Item::initAnim()
{
	addAnimation(ANIM_HEART_ITEM_IDLE);
	addAnimation(ANIM_DAGGER_ITEM_IDLE);
	addAnimation(ANIM_WHIP_ITEM_IDLE);
}

