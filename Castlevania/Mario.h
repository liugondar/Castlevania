#pragma once
#include "GameObject.h"

constexpr auto MARIO_WALKING_SPEED = 0.1f;
constexpr auto MARIO_JUMP_SPEED_Y =0.5f;
constexpr auto MARIO_JUMP_DEFLECT_SPEED = 0.2f;
constexpr auto MARIO_GRAVITY = 0.002f;

#define MARIO_STATE_IDLE	ANIMATION_MARIO_IDLE_LEFT
constexpr auto MARIO_STATE_WALKING_RIGHT = 100;
constexpr auto MARIO_STATE_WALKING_LEFT = 200;
constexpr auto MARIO_STATE_JUMP = 300;
constexpr auto MARIO_BIG_BBOX_WIDTH = 15;
constexpr auto MARIO_BIG_BBOX_HEIGHT = 27;

class Mario :
	public GameObject
{
public:
	void setState(int state);
	void render();
	void checkBound(DWORD dt);

	void updateVelocity();
	void checkOutOfGround();

	// Inherited via GameObject
	virtual void update(DWORD dt, vector<LPGameObject> *coObject=nullptr);
	virtual Box getBoundingBox() override;

};

