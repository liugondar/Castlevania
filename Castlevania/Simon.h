#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "Item.h"
#include "Constants.h"
#include "SetTimeOut.h"
#include <conio.h>
#include "SimonConstants.h"
#include "SubWeapon.h"
//states
enum SimonState
{
	idle= 1,
	walking=2,
	sitting=3,
	jumping=4,
	hitting=5,
	hittingWhenSitting=6,
	throwing=7,
	throwingWhenSitting=8
};

class Simon :
	public GameObject
{
	bool isHitting{};
	bool isThrowing{};
	bool isReleaseSitButton;
	bool isOneTimeAnim{};
	Whip* whip;
	SubWeapon* subWeapon{};
	bool isInGround;
public:
	Simon();
	~Simon();

	void handleOnKeyPress(BYTE *states);
	void handleOnKeyDown(int KeyCode );
	void handleOnKeyRelease(int KeyCode);
	void move(int side);
	void jump();
	void sit();
	void stand();
	void standUp();
	void hit();
	void hitWhenSitting();
	void throwing();
	void throwingWhenSitting();
	void throwSubWeapon();
	void beginFight();
	void resetState();

	
	// Inherited via GameObject
	void setState(int state);
	void update(DWORD dt, vector<LPGameObject> *coObjects = nullptr, 
		vector<LPGameObject>* canHitObjects=nullptr) ;
	void processCollisionWithGround(float minTy, float ny);
	void checkCollision(DWORD dt, vector<LPGameObject> *coObject);
	void processCollisionWithItem(Item* item);
	void checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks);
	void checkCollisionWithItems(vector<GameObject*> * items = nullptr);

	virtual void render() override;
	void updateAnimId();

	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

	void initAnim() override;
};

