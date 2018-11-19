#include "Simon.h"
#include "GameObjectManger.h"
#include "DaggerSubWeapon.h"

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
	if (KeyCode == DIK_DOWN) {
		isReleaseSitButton = true;
		if (isInGround && !isHitting && !isThrowing) {
			standUp();
		}
	}
}

void Simon::handleOnKeyPress(BYTE * states)
{
	auto game = Game::getInstance();

	if (isHitting || isThrowing) return;
	if (currentState == SimonState::sitting) return;
	if (currentState == SimonState::jumping) return;

	if (game->isKeyDown(DIK_RIGHT)) {
		move(FaceSide::right);
	}
	else if (game->isKeyDown(DIK_LEFT)) {
		move(FaceSide::left);
	}
	else if (game->isKeyDown(DIK_DOWN)) {
		if (isInGround) {
			isReleaseSitButton = false;
			sit();
		}
	}

	else {
		stand();
	}
}

void Simon::handleOnKeyDown(int keyCode)
{
	if (isHitting || isThrowing) return;

	if (keyCode == DIK_SPACE) {
		if (previousState != SimonState::jumping&& isInGround && !isHitting) {
			jump();
		}
	}
	else if (keyCode == DIK_LCONTROL) {
		if (!isReleaseSitButton) {
			hitWhenSitting();
		}
		else {
			hit();
		}
	}
	else if (keyCode == DIK_A)
	{
		if (!isReleaseSitButton)
			throwingWhenSitting();
		else throwing();
	}
	else if (keyCode == DIK_DOWN)
	{
		if (isInGround
			&& currentState != SimonState::sitting
			&& currentState != SimonState::jumping
			)
		{
			isReleaseSitButton = false;
			sit();
		}
	}
}

void Simon::move(int side)
{
	faceSide = side;
	setState(SimonState::walking);
	vx = faceSide == FaceSide::left ? -SIMON_VX : SIMON_VX;
}

void Simon::jump()
{
	setState(SimonState::jumping);
	vy = -SIMON_VJUMP;
	isInGround = false;
}

void Simon::sit()
{
	y = y + (SIM_MOVE_H - SIM_SIT_H);
	setState(SimonState::sitting);
	vx = 0;
	vy = 0;
}

void Simon::stand()
{
	resetState();
	setState(SimonState::idle);
	vx = 0;
}

void Simon::standUp()
{
	resetState();
	setState(SimonState::idle);
	y = y - (SIM_MOVE_H - SIM_SIT_H);
}

void Simon::hit()
{
	vx = 0;
	isHitting = true;
	setState(SimonState::hitting);
}

void Simon::hitWhenSitting()
{
	vx = 0;
	vy = 0;
	isHitting = true;
	setState(SimonState::hittingWhenSitting);
}

void Simon::throwing()
{
	if (!subWeapon) return;
	if (subWeapon->getState() == SubWeaponState::active) return;
	vx = 0;
	vy = 0;
	isThrowing = true;
	setState(SimonState::throwing);
}

void Simon::throwingWhenSitting()
{
	if (!subWeapon) return;
	if (subWeapon->getState() == SubWeaponState::active) return;
	vx = 0;
	vy = 0;
	isThrowing = true;
	setState(SimonState::throwingWhenSitting);
}

void Simon::throwSubWeapon()
{
	if (!subWeapon) return;
	if (subWeapon->getState() == SubWeaponState::active) return;

	subWeapon->setSide(faceSide);
	const auto subX = faceSide == FaceSide::left ? x - SIM_HIT_W + 10 : x + SIM_HIT_W - 10;
	const auto subY = y + 16;

	subWeapon->setPosition(subX, subY);
	subWeapon->setState(SubWeaponState::active);
}

void Simon::beginFight()
{
}

void Simon::resetState()
{
	isHitting = false;
	isThrowing = false;
}

void Simon::update(DWORD dt, vector<LPGameObject>* bricks, vector<LPGameObject>* gameObjects, vector<GameObject*>* items)
{
	GameObject::update(dt);
	whip->update(dt, x, y, gameObjects);
	if (subWeapon) subWeapon->update(dt, gameObjects);

	checkCollisionWithItems(items);
	checkCollisionWithGround(dt, bricks);
	auto newPositionX = x + dx;
	if (newPositionX >= 0 && newPositionX + SIM_MOVE_W <= boundingGameX) {
		x = newPositionX;
	}
	updateAnimId();
	// simple fall down
	vy += dt * SIMON_GRAVITY;
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
			if (item->getType() == ItemType::heartItem) {
			}
			else if (item->getType() == ItemType::whipItem) {
				if (whip)whip->upgradeWhipLv();
			}
			else if (item->getType() == ItemType::daggerItem) {
				subWeapon = new DaggerSubWeapon();
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
	if (subWeapon)
	{
		subWeapon->render();
	}
	animations[animationId]->render(x, y);
	previousAmiId = animationId;
}

void Simon::updateAnimId()
{

	if (currentState == SimonState::walking) {
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_WALKING_L
			: ANIM_SIM_WALKING_R;
	}
	else if (currentState == SimonState::sitting) {
		if (isReleaseSitButton) {
			standUp();
		}
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_SITTING_L
			: ANIM_SIM_SITTING_R;
	}
	else if (currentState == SimonState::jumping) {
		if (vy > 0.15)
		{
			animationId = faceSide == FaceSide::left
				? ANIM_SIM_IDLE_L
				: ANIM_SIM_IDLE_R;
		}
		else
		{
			animationId = faceSide == FaceSide::left
				? ANIM_SIM_SITTING_L
				: ANIM_SIM_SITTING_R;
		}
	}
	else if (currentState == SimonState::hitting) {
		// set hitting anim
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_HITTING_L
			: ANIM_SIM_HITTING_R;
		// check and process if animation hitting is done
		if (animations[animationId]) {
			if (animations[animationId]->isDone()) {
				whip->refreshAnim();
				animations[animationId]->refresh();
				stand();
				animationId = faceSide == FaceSide::left
					? ANIM_SIM_IDLE_L
					: ANIM_SIM_IDLE_R;
			}
		}
	}
	else if (currentState == SimonState::hittingWhenSitting) {
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_HIT_WHEN_SITTING_L
			: ANIM_SIM_HIT_WHEN_SITTING_R;
		if (animations[animationId]) {
			const auto frame = animations[animationId]->getFrame();
			if (animations[animationId]->isDone()) {
				whip->refreshAnim();
				isHitting = false;
				setState(SimonState::sitting);
				animations[animationId]->refresh();
				animationId = faceSide == FaceSide::left
					? ANIM_SIM_IDLE_L
					: ANIM_SIM_IDLE_R;
			}
		}
	}
	else if (currentState == SimonState::throwing)
	{
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_HITTING_L
			: ANIM_SIM_HITTING_R;
		if (animations[animationId]) {
			const auto frame = animations[animationId]->getFrame();
			if (frame == 2) throwSubWeapon();
			else if (animations[animationId]->isDone())
			{
				animations[animationId]->refresh();
				stand();
			}
		}
	}
	else if (currentState == SimonState::throwingWhenSitting)
	{
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_HIT_WHEN_SITTING_L
			: ANIM_SIM_HIT_WHEN_SITTING_R;
		if (animations[animationId]) {
			const auto frame = animations[animationId]->getFrame();
			if (frame == 2) throwSubWeapon();
			else if (animations[animationId]->isDone())
			{
				animations[animationId]->refresh();
				setState(SimonState::sitting);
				isThrowing = false;
				animationId = faceSide == FaceSide::left
					? ANIM_SIM_IDLE_L
					: ANIM_SIM_IDLE_R;
			}
		}
	}
	else {
		animationId = faceSide == FaceSide::left
			? ANIM_SIM_IDLE_L
			: ANIM_SIM_IDLE_R;
	}
}

void Simon::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	float width, height;

	if (currentState == SimonState::sitting ||
		(currentState == SimonState::jumping) ||
		currentState == SimonState::hittingWhenSitting ||
		currentState == SimonState::throwingWhenSitting
		) {
		width = SIM_SIT_W;
		height = SIM_SIT_H;
	}
	else {
		width = SIM_MOVE_W;
		height = SIM_MOVE_H;
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
			isInGround = true;
			if (currentState == SimonState::jumping)
				standUp();
		}
	}

	for (auto& coEvent : coEvents) delete coEvent;
}
