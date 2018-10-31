#pragma once
#include "GameObject.h"

constexpr auto GOOMBA_WALKING_SPEED = 0.05f;

constexpr auto GOOMBA_BBOX_WIDTH = 16;
constexpr auto GOOMBA_BBOX_HEIGHT = 14;
constexpr auto GOOMBA_BBOX_HEIGHT_DIE = 9;
constexpr auto GOOMBA_GRAVITY = 0.002f;

constexpr auto GOOMBA_STATE_WALKING = 100;
constexpr auto GOOMBA_STATE_DIE = 200;



class Goomba: public GameObject
{
public:
	Goomba();
	~Goomba();

	void checkBoundingScreen();

	// Inherited via GameObject
	void update(DWORD dt, vector<LPGameObject> *coObject = nullptr);

	bool isCollisionWithGround(vector<GameObject* >* coObjects);

	virtual void render() override;
	virtual Box getBoundingBox() override;
	virtual void setState(int state);
};

