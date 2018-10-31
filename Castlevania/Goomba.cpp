#include "Goomba.h"



Goomba::Goomba()
{
}


Goomba::~Goomba()
{
}

void Goomba::checkBoundingScreen()
{

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) {
		faceSide = FACE_TO_LEFT;
		vx = -vx;
		x = 290;
	}
	if (vx < 0 && x < SCREEN_LEFT) {
		faceSide = FACE_TO_RIGHT;
		x = SCREEN_LEFT; vx = -vx;
	}
}

void Goomba::update(DWORD dt, vector<LPGameObject>* blockGrounds)
{
	vy = 0;
	GameObject::update(dt);
	auto checkGround=isCollisionWithGround(blockGrounds);

	/*x += dx;
	y += dy;*/
	vy += GOOMBA_GRAVITY * dt;
	checkBoundingScreen();
}

bool Goomba::isCollisionWithGround(vector<GameObject*>* coObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;
	coEvents.clear();
	coEventsResult.clear();

	calcPotentialCollisions(coObjects, coEvents);
	if (coObjects->size() == 0) {
		x += dy;
		y += dy;
		return false;
	}
	else {
		float minTx, minTy, nx=0,ny;
		filterCollision(coEvents, coEventsResult, minTx, minTy, nx, ny);
		y += minTy * dy + ny * 0.4f;
		x += minTx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		return true;
	}
}



void Goomba::render()
{
	RenderBoundingBox();
	int animationId;
	if (getState() == GOOMBA_STATE_WALKING) {
		animationId = ANIMATION_GOOMBA_WALKING;
	}
	else {
		animationId = ANIMATION_GOOMBA_DEAD;
	}

	animations[animationId]->render(x, y);
}

Box Goomba::getBoundingBox()
{
	Box box;
	box.left = x;
	box.top = y;
	box.right = x + GOOMBA_BBOX_WIDTH;
	box.bottom = y + GOOMBA_BBOX_HEIGHT;

	return box;
}

void Goomba::setState(int state)
{
	GameObject::setState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
	}
}
