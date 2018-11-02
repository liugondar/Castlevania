#include "Simon.h"



Simon::Simon()
{
}


Simon::~Simon()
{
}


void Simon::setState(int state)
{
	GameObject::setState(state);
}


void Simon::handleOnKeyRelease(int KeyCode)
{
	if (KeyCode == DIK_DOWN) {
		Sleep(100);
		y = y - (SIMON_MOVING_HEIGHT - SIMON_SITTING_HEIGHT);
		setState(STATE_SIMON_IDLE);
	}
}

void Simon::moveLeft()
{
	vx = -SIMON_VX;
	faceSide = FaceSide::left;
}

void Simon::moveRight()
{

	vx = SIMON_VX;
	faceSide = FaceSide::right;
}

void Simon::jump()
{
	vy = -SIMON_VJUMP;
}

void Simon::sit()
{
	vx = 0;
	vy = 0;
}

void Simon::stand()
{
	vx = 0;
}

void Simon::hit()
{
}

void Simon::beginFight()
{
}

void Simon::update(DWORD dt, vector<LPGameObject>* coObject)
{
	GameObject::update(dt);

	checkCollisionWithGround(dt, coObject);
	// simple fall down
	vy += dt * SIMON_GRAVITY;
}

void Simon::render()
{
	RenderBoundingBox();
	auto animationId = ANIMATION_SIMON_IDLE_FACE_RIGHT;

	if (currentState == STATE_SIMON_IDLE) {
		if (faceSide == FaceSide::left)  animationId = ANIMATION_SIMON_IDLE_FACE_LEFT;
		if (faceSide == FaceSide::right) animationId = ANIMATION_SIMON_IDLE_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_SITTING) {
		if (faceSide == FaceSide::left)  animationId = ANIMATION_SIMON_SIT_FACE_LEFT;
		if (faceSide == FaceSide::right) animationId = ANIMATION_SIMON_SIT_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_JUMPING) {
		if (faceSide == FaceSide::left)  animationId = ANIMATION_SIMON_SIT_FACE_LEFT;
		if (faceSide == FaceSide::right) animationId = ANIMATION_SIMON_SIT_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_HITTING) {
		animationId = ANIMATION_SIMON_HITTING_LEFT;
	}
	else {
		if (currentState == STATE_SIMON_WALKING_LEFT) animationId = ANIMATION_SIMON_WALKING_LEFT;
		if (currentState == STATE_SIMON_WALKING_RIGHT) animationId = ANIMATION_SIMON_WALKING_RIGHT;
	}
	animations[animationId]->render(x, y);
}

Box Simon::getBoundingBox()
{
	auto width = SIMON_MOVING_WIDTH;
	auto height = SIMON_MOVING_HEIGHT;

	if (currentState == STATE_SIMON_SITTING) {
		width = SIMON_SITTING_WIDTH;
		height = SIMON_SITTING_HEIGHT;
	}
	auto box = Box();
	box.left = x;
	box.top = y;
	box.right = x + width;
	box.bottom = y + height;
	box.vx = vx;
	box.vy = vy;
	return box;
}

void Simon::checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks)
{
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();

	calcPotentialCollisions(bricks, coEvents);

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
		if (ny != 0) {
			vy = 0;
			if (currentState == STATE_SIMON_JUMPING)setState(STATE_SIMON_IDLE);
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void Simon::handleOnKeyPress(BYTE * states)
{
	auto simonState = getState();
	auto game = Game::getInstance();
	if (simonState == STATE_SIMON_SITTING
		|| simonState == STATE_SIMON_HITTING
		|| simonState == STATE_SIMON_JUMPING) {
		return;
	}
	else {

		if (game->isKeyDown(DIK_RIGHT)) {
			setState(STATE_SIMON_WALKING_RIGHT);
			moveRight();
		}
		else if (game->isKeyDown(DIK_LEFT)) {
			setState(STATE_SIMON_WALKING_LEFT);
			moveLeft();
		}
		else if (game->isKeyDown(DIK_DOWN)) {
			if (getState() != STATE_SIMON_SITTING) {
				y = y + (SIMON_MOVING_HEIGHT - SIMON_SITTING_HEIGHT);
				setState(STATE_SIMON_SITTING);
				sit();
			}
		}
		else {
			setState(STATE_SIMON_IDLE);
			stand();
		}
	}
}

void Simon::handleOnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (previousState != STATE_SIMON_JUMPING) {
			setState(STATE_SIMON_JUMPING);
			jump();
		}
		break;
	case DIK_LCONTROL:
		setState(STATE_SIMON_HITTING);
		hit();
		break;
	}
}
