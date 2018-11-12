#pragma once
#include "GameObject.h"
#include "SimonConstants.h"

constexpr auto WHIP_WIDTH = 42;
constexpr auto WHIP_HEIGHT = 19;

constexpr auto STATE_WHIP_READY_HIT = 0;
constexpr auto STATE_WHIP_START_HIT= 1;
constexpr auto STATE_WHIP_HITTING= 2;
constexpr auto STATE_WHIP_DISAPPEAR= 3;

class Whip: public GameObject
{
public:
	Whip();
	~Whip();

	void checkEnemyCollisions(vector<LPGameObject> coObject );
	// Inherited via GameObject
	virtual void render() override;
	void update(DWORD dt, float x, float y, vector<LPGameObject> *coObject);
	void setSide(FaceSide side);
	void refreshAnim();
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
};
