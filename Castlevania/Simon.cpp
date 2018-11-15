#include "Simon.h"
#include "GameObjectManger.h"

Simon::Simon()
{
	whip = new Whip();
	whip->setPosition(x, y);
	isInGround = true;
	isReleaseSitButton = true;
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
		isReleaseSitButton = true;
		if (isInGround && !isHitting) {
			DebugOut(L"is hitting %d\n", isHitting);
			standUp();
		}
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
			if (!isHitting) move(FaceSide::right);
		}
		else if (game->isKeyDown(DIK_LEFT)) {
			if (!isHitting) move(FaceSide::left);
		}
		else if (game->isKeyDown(DIK_DOWN)) {
			if (simonState != STATE_SIMON_SITTING
				&& isInGround
				&& simonState != STATE_SIMON_JUMPING
				&& !isHitting)
			{
				isReleaseSitButton = false;
				sit();
			}
		}
		else {
			if (!isHitting) stand();
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
		if (!isReleaseSitButton) {
			hitWhenSitting();
		}
		else {
			hit();
		}
	}
}

void Simon::move(int side)
{
	faceSide = side;
	setState(STATE_SIMON_WALKING);
	vx = faceSide == FaceSide::left ? -SIMON_VX : SIMON_VX;
}

void Simon::jump()
{
	setState(STATE_SIMON_JUMPING);
	vy = -SIMON_VJUMP;
	isInGround = false;
}

void Simon::sit()
{
	y = y + (SIM_MOVE_H - SIM_SIT_H);
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
	isHitting = false;
	setState(STATE_SIMON_IDLE);
	y = y - (SIM_MOVE_H - SIM_SIT_H);
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
	isHitting = true;
	setState(STATE_SIMON_HIT_WHEN_SITTING);
}

void Simon::beginFight()
{
}

void Simon::update(DWORD dt, vector<LPGameObject>* bricks, vector<LPGameObject>* gameObjects, vector<GameObject*>* items)
{
	GameObject::update(dt);
	whip->update(dt, x, y, gameObjects);

	checkCollisionWithItems(items);
	checkCollisionWithGround(dt, bricks);
	auto newPositionX = x + dx;
	if (newPositionX >= 0 && newPositionX + SIM_MOVE_W <= boundingGameX) {
		x = newPositionX;
	}

	updateAnimId();
	vy += dt * SIMON_GRAVITY;
	// simple fall down
}

void Simon::checkCollisionWithItems(vector<GameObject*>* items)
{
	vector<LPCollisionEvent> coEvents;
	vector<LPCollisionEvent> coEventsResult;
	coEvents.clear();

	calcPotentialCollisions(items, coEvents);

	if (!coEvents.empty()) {
		float minTx, minTy, nx = 0, ny;
		filterCollision(coEvents, coEventsResult, minTx, minTy, nx, ny);
		for (auto& i : coEventsResult)
		{
			const auto item = i->obj;
			if (item->getType() == ItemType::heart) {
			}
			else if (item->getType() == ItemType::whip) {
			}
			item->setState(State::dead);
		}
	}

	for (auto& coEvent : coEvents) delete coEvent;
}

void Simon::render()
{
	if (isHitting) {
		whip->setSide(faceSide);
		whip->render();
	}
	animations[animationId]->render(x, y, isOneTimeAnim);
	previousAmiId = animationId;
}

void Simon::updateAnimId()
{

	isOneTimeAnim = false;

	if (currentState == STATE_SIMON_WALKING) {
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_WALKING_LEFT
			: ANIM_SIM_WALKING_RIGHT;
	}
	else if (currentState == STATE_SIMON_SITTING) {
		if (isReleaseSitButton) {
			standUp();
		}
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_SIT_FACE_LEFT
			: ANIM_SIM_SIT_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_JUMPING) {
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_SIT_FACE_LEFT
			: ANIM_SIM_SIT_FACE_RIGHT;
	}
	else if (currentState == STATE_SIMON_HITTING) {
		// set hitting anim
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_HIT_LEFT
			: ANIM_SIM_HIT_RIGHT;
		isOneTimeAnim = true;
		// check and process if animation hitting is done
		if (animations[animationId]) {
			auto frame = animations[animationId]->getFrame();
			if (frame == 3) {
				whip->refreshAnim();
				animations[animationId]->refresh();
				stand();
				animationId = faceSide == FaceSide::left
					? ANIM_SIM_IDLE_FACE_LEFT
					: ANIM_SIM_IDLE_FACE_RIGHT;
			}
		}
	}
	else if (currentState == STATE_SIMON_HIT_WHEN_SITTING) {
		// set hitting anim
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_HIT_WHEN_SIT_LEFT
			: ANIM_SIM_HIT_WHEN_SIT_RIGHT;

		isOneTimeAnim = true;

		// check and process if animation hitting is done
		if (animations[animationId]) {
			auto frame = animations[animationId]->getFrame();
			if (frame == 3) {
				whip->refreshAnim();
				animations[animationId]->refresh();
				setState(STATE_SIMON_SITTING);
				isHitting = false;
				animationId = faceSide == FaceSide::left
					? ANIM_SIM_SIT_FACE_LEFT
					: ANIM_SIM_SIT_FACE_RIGHT;
			}
		}
	}
	else {
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_IDLE_FACE_LEFT
			: ANIM_SIM_IDLE_FACE_RIGHT;

	}
}

void Simon::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	auto width = SIM_MOVE_W;
	auto height = SIM_MOVE_H;

	if (currentState == STATE_SIMON_SITTING ||
		(currentState == STATE_SIMON_JUMPING) ||
		currentState == STATE_SIMON_HIT_WHEN_SITTING) {
		width = SIM_SIT_W;
		height = SIM_SIT_H;
	}

	if (currentState == STATE_SIMON_HITTING) {
		if (previousState == STATE_SIMON_SITTING) {
			width = SIM_SIT_W;
			height = SIM_SIT_H;
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

