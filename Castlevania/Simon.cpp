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
		y = y - (SIMON_MOVING_HEIGHT - SIMON_SITTING_HEIGHT);
		stand();
	}

	if (KeyCode == DIK_LCONTROL) {
		if (game->isKeyDown(DIK_LEFT) || game->isKeyDown(DIK_RIGHT))return;
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
			moveRight();
		}
		else if (game->isKeyDown(DIK_LEFT)) {
			moveLeft();
		}
		else if (game->isKeyDown(DIK_DOWN)) {
			if (simonState != STATE_SIMON_SITTING && isInGround && simonState != STATE_SIMON_JUMPING) {
				y = y + (SIMON_MOVING_HEIGHT - SIMON_SITTING_HEIGHT);
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
		if (previousState != STATE_SIMON_JUMPING && isInGround) {
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
	else {
		whip->refreshAnim();
	}
}


void Simon::moveLeft()
{
	isHitting = false;
	setState(STATE_SIMON_WALKING_LEFT);
	vx = -SIMON_VX;
	faceSide = FaceSide::left;
}

void Simon::moveRight()
{
	isHitting = false;
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

void Simon::hit()
{
	vx = 0;
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
	animationId = ANIMATION_SIMON_IDLE_FACE_RIGHT;
	bool isOneTimeAnim = false;

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
		if (faceSide == FaceSide::left)  animationId = ANIMATION_SIMON_HITTING_LEFT;
		if (faceSide == FaceSide::right) animationId = ANIMATION_SIMON_HITTING_RIGHT;
		isOneTimeAnim = true;
		if (animations[animationId]) {
			auto frame = animations[animationId]->getFrame();
			if (frame == 3) {
				whip->refreshAnim();
				setState(STATE_SIMON_IDLE);
				animationId = faceSide == FaceSide::left ? ANIMATION_SIMON_IDLE_FACE_LEFT : ANIMATION_SIMON_IDLE_FACE_RIGHT;
			}
		}
	}
	else {
		if (currentState == STATE_SIMON_WALKING_LEFT) animationId = ANIMATION_SIMON_WALKING_LEFT;
		if (currentState == STATE_SIMON_WALKING_RIGHT) animationId = ANIMATION_SIMON_WALKING_RIGHT;
	}
	// refresh animation one time state
	auto isFirstTime = previousAmiId == -1;
	auto notSameAnim = previousAmiId != animationId;
	auto canRefreshAnim = !isFirstTime
		&& (notSameAnim || !isReleaseHitButton)
		&& animations[animationId]->isDone()
		&& previousAnimIsOneTimeAnim;

	if (canRefreshAnim) {
		animations[previousAmiId]->refresh();
		whip->refreshAnim();
	}

	animations[animationId]->render(x, y, isOneTimeAnim);
	previousAmiId = animationId;
	previousAnimIsOneTimeAnim = isOneTimeAnim;

	if (isHitting && !animations[animationId]->isDone())
	{
		whip->setSide(faceSide);
		whip->render();
	}
	else {
		whip->refreshAnim();
	}

	animations[animationId]->render(x, y, isOneTimeAnim);
}

void Simon::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	auto width = SIMON_MOVING_WIDTH;
	auto height = SIMON_MOVING_HEIGHT;

	if (currentState == STATE_SIMON_SITTING) {
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
			if (currentState == STATE_SIMON_JUMPING)setState(STATE_SIMON_IDLE);
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

