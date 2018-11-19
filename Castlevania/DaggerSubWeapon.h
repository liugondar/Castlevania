#pragma once
#include "SubWeapon.h"

constexpr auto DAGGER_W = 32;
constexpr auto DAGGER_H = 18;
constexpr auto DAGGER_VX = 0.3f;

class DaggerSubWeapon :
	public SubWeapon
{
public:
	DaggerSubWeapon();
	~DaggerSubWeapon();
	void checkEnemyCollisions(vector<LPGameObject>* coObject);

	void render() override;
	void getBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void update(DWORD dt, vector<GameObject*>* coObjects) override;
};

