#include "Simon.h"

Simon::Simon()
{
	whip = new Whip();
	whip->setPosition(x, y);
	isInGround = true;
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
	auto game = Game::getInstance();
	if (KeyCode == DIK_DOWN) {
		if (isInGround) {
			standUp();
		}
	}

	if (KeyCode == DIK_LCONTROL) {
		isReleaseHitButton = true;
	}
}


void Simon::handleOnKeyPress(BYTE * states)
{
	auto simonState = getState();
	auto game = Game::getInstance();

	if (simonState == STATE_SIMON_SITTING
		|| simonState == STATE_SIMON_JUMPING) {
		return;
	}
	else {

		if (game->isKeyDown(DIK_RIGHT)) {
			if (!isHitting) moveRight();
		}
		else if (game->isKeyDown(DIK_LEFT)) {
			if (!isHitting) moveLeft();
		}
		else if (game->isKeyDown(DIK_DOWN)) {
			if (simonState != STATE_SIMON_SITTING && isInGround && simonState != STATE_SIMON_JUMPING) {
				sit();
			}
		}
		else if (currentState != STATE_SIMON_HITTING) {
			stand();
		}
	}
}

void Simon::handleOnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_SPACE) {
		if (previousState != STATE_SIMON_JUMPING && isInGround && !isHitting) {
			jump();
		}
	}
	else if (KeyCode == DIK_LCONTROL) {
		if (Game::getInstance()->isKeyDown(DIK_DOWN)) {
			DebugOut(L"hitting");
		}
		else {
			isHitting = true;
			isReleaseHitButton = false;
			hit();
		}
	}
}


void Simon::moveLeft()
{
	setState(STATE_SIMON_WALKING_LEFT);
	vx = -SIMON_VX;
	faceSide = FaceSide::left;
}

void Simon::moveRight()
{
	setState(STATE_SIMON_WALKING_RIGHT);
	vx = SIMON_VX;
	faceSide = FaceSide::right;
}

void Simon::jump()
{
	setState(STATE_SIMON_JUMPING);
	vy = -SIMON_VJUMP;
	isInGround = false;
}

void Simon::sit()
{
	y = y + (SIMON_MOVING_HEIGHT - SIMON_SITTING_HEIGHT);
	setState(STATE_SIMON_SITTING);
	vx = 0;
	vy = 0;
}

void Simon::stand()
{
	isHitting = false;
	setState(STATE_SIMON_IDLE);
	vx = 0;
}

void Simon::standUp()
{
	setState(STATE_SIMON_IDLE);
	y = y - (SIMON_MOVING_HEIGHT - SIMON_SITTING_HEIGHT);
}

void Simon::hit()
{
	vx = 0;
	isHitting = true;
	setState(STATE_SIMON_HITTING);
}

void Simon::hitWhenSitting()
{
	vx = 0;
	vy = 0;
	setState(STATE_SIMON_HIT_WHEN_SITTING);
}

void Simon::beginFight()
{
}

void Simon::update(DWORD dt, vector<LPGameObject>* coObject, vector<LPGameObject>* gameObjects)
{
	GameObject::update(dt);
	whip->update(dt, x, y, gameObjects);

	checkCollisionWithGround(dt, coObject);
	auto newPositionX = x + dx;
	if (newPositionX >= 0 && newPositionX + SIMON_MOVING_WIDTH <= boundingGameX) {
		x = newPositionX;
	}

	vy += dt * SIMON_GRAVITY;
	// simple fall down
}

void Simon::render()
{
	RenderBoundingBox();
	animationId = ANIMATION_SIMON_IDLE_FACE_RIGHT;
	bool isOneTimeAnim = false;

	if (currentState == STATE_SIMON_IDLE) {
		animationId = faceSide == FaceSide::left
			? ANIMATION_SIMON_IDLE_FACE_LEFT
			: ANIMATION_SIMON_IDLE_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_SITTING) {
		animationId = faceSide == FaceSide::left
			? ANIMATION_SIMON_SIT_FACE_LEFT
			: ANIMATION_SIMON_SIT_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_JUMPING) {
		animationId = faceSide == FaceSide::left
			? ANIMATION_SIMON_SIT_FACE_LEFT
			: ANIMATION_SIMON_SIT_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_HITTING) {
		// set hitting anim
		animationId = faceSide == FaceSide::left
			? ANIMATION_SIMON_HITTING_LEFT
			: ANIMATION_SIMON_HITTING_RIGHT;

		isOneTimeAnim = true;

		// check and process if animation hitting is done
		if (animations[animationId]) {
			auto frame = animations[animationId]->getFrame();
			if (frame == 3) {
				whip->refreshAnim();
				animations[animationId]->refresh();
				stand();
					animationId = faceSide == FaceSide::left
					? ANIMATION_SIMON_IDLE_FACE_LEFT
					: ANIMATION_SIMON_IDLE_FACE_RIGHT;
			}
		}
	}
	else {
		animationId = faceSide == FaceSide::left
			? ANIMATION_SIMON_WALKING_LEFT
			: ANIMATION_SIMON_WALKING_RIGHT;
	}

	if (isHitting) {
		whip->setSide(faceSide);
		whip->render();
	}
	animations[animationId]->render(x, y, isOneTimeAnim);
	previousAmiId = animationId;
	previousAnimIsOneTimeAnim = isOneTimeAnim;

}

void Simon::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	auto width = SIMON_MOVING_WIDTH;
	auto height = SIMON_MOVING_HEIGHT;

	if (currentState == STATE_SIMON_SITTING || (currentState== STATE_SIMON_JUMPING)) {
		width = SIMON_SITTING_WIDTH;
		height = SIMON_SITTING_HEIGHT;
	}

	if (currentState == STATE_SIMON_HITTING) {
		if (previousState == STATE_SIMON_SITTING) {
			width = SIMON_SITTING_WIDTH;
			height = SIMON_SITTING_HEIGHT;
		}
	}
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Simon::checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks)
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
			isInGround = true;
			if (currentState == STATE_SIMON_JUMPING)
			{
				standUp();
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

