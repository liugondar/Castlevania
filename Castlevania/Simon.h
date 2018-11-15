#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "Constants.h"
#include "SetTimeOut.h"
#include <conio.h>
#include "SimonConstants.h"

class Simon :
	public GameObject
{
	bool isHitting;
	bool isReleaseSitButton;
	bool isOneTimeAnim;
	Whip* whip;
	bool isInGround;
public:
	Simon();
	~Simon();

	void checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks);

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
	void beginFight();

	
	// Inherited via GameObject
	void setState(int state);
	virtual void update(DWORD dt, vector<LPGameObject> *coObject = nullptr, vector<LPGameObject>* gameObject=nullptr);
	virtual void render() override;
	void updateAnimId();
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

};

