#include "Mario.h"
void Mario::setState(int state)
{
	GameObject::setState(state);
	updateVelocity();
}
// Update mario atribute ( state, position) when mario receive events
void Mario::update(DWORD dt, vector<LPGameObject> *coObject)
{

	GameObject::update(dt);

	//dx = vx * dt;
	//dy = vy * dt;
/*
	x += vx * dt;
	y += vy * dt*/;

	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();

	calcPotentialCollisions(coObject, coEvents);

	// no collison
	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
	

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		if (nx != 0) DebugOut(L"mario collision");
	}

	// simple fall down
	vy += MARIO_GRAVITY * dt;
	checkBound(dt);

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}
// Update velocity of marito
void Mario::updateVelocity() {
	switch (currentState)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		break;

	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		break;

	case MARIO_STATE_JUMP:
			vy = -MARIO_JUMP_SPEED_Y;

	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	}
}
// Check if mario out of area ( where mario is inValid) => set it to boundary
void Mario::checkBound(DWORD dt)
{
	checkOutOfGround();
}
// Check boundary in ground
void Mario::checkOutOfGround()
{
	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

Box Mario::getBoundingBox()
{
	auto box = Box();
	box.left = x;
	box.top = y;
	box.right = x + MARIO_BIG_BBOX_WIDTH;
	box.bottom = y + MARIO_BIG_BBOX_HEIGHT;
	box.vx = vx;
	box.vy = vy;
	return box;
}
// Render mario
void Mario::render()
{
	RenderBoundingBox();
	int animationId;
	// vc==0 => mario is idle
	if (vx == 0) {
		if (faceSide > 0) animationId = ANIMATION_MARIO_IDLE_RIGHT;
		else animationId = ANIMATION_MARIO_IDLE_LEFT;
	}
	else if (vx > 0) {
		animationId = ANIMATION_MARIO_FACE_RIGHT;
	}
	else
	{
		animationId = ANIMATION_MARIO_FACE_LEFT;
	}
	animations[animationId]->render(x, y);
}
