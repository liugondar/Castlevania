#include "Item.h"
#include "GameObjectManger.h"


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

	for (auto& coEvent : coEvents) delete coEvent;
}

void Item::update(DWORD dt, vector<LPGameObject>* bricks)
{
	GameObject::update(dt);
	checkCollisionWithGround(dt,bricks);
	vy += 0.002f* dt;
}

