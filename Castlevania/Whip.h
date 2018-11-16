#pragma once
#include "GameObject.h"
#include "SimonConstants.h"

constexpr auto WHIP_LV1_READY_W = 16;
constexpr auto WHIP_LV1_READY_H = 50;
constexpr auto WHIP_LV1_START_HIT_W = 32;
constexpr auto WHIP_LV1_START_HIT_H = 40;
constexpr auto WHIP_LV1_HITTING_W = 45;
constexpr auto WHIP_LV1_HITTING_H = 12;

constexpr auto WHIP_LV2_READY_W= 16;
constexpr auto WHIP_LV2_READY_H= 50;
constexpr auto WHIP_LV2_START_HIT_W= 32;
constexpr auto WHIP_LV2_START_HIT_H= 40;
constexpr auto WHIP_LV2_HITTING_W= 45;
constexpr auto WHIP_LV2_HITTING_H= 12;

constexpr auto WHIP_LV3_READY_W= 16;
constexpr auto WHIP_LV3_READY_H= 50;
constexpr auto WHIP_LV3_START_HIT_W= 32;
constexpr auto WHIP_LV3_START_HIT_H= 40;
constexpr auto WHIP_LV3_HITTING_W= 78;
constexpr auto WHIP_LV3_HITTING_H= 12;

constexpr auto STATE_WHIP_READY_HIT = 0;
constexpr auto STATE_WHIP_START_HIT = 1;
constexpr auto STATE_WHIP_HITTING = 2;
constexpr auto STATE_WHIP_DISAPPEAR = 3;

constexpr auto MAX_WHIP_LV = 3;

class Whip : public GameObject
{
	int lv;
public:
	Whip();
	~Whip();

	void checkEnemyCollisions(vector<LPGameObject> coObject);
	// Inherited via GameObject
	virtual void render() override;
	void update(DWORD dt, float x, float y, vector<LPGameObject> *coObject);
	void setSide(int side);
	void refreshAnim();
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void upgradeWhipLv();
};

