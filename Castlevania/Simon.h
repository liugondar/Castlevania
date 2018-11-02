#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Input.h"

class Simon :
	public GameObject
{
public:
	Simon();
	~Simon();

	void checkCollisionWithGround(DWORD dt, vector<LPGameObject> *bricks);

	void handleOnKeyPress(BYTE *states);
	void handleOnKeyDown(int KeyCode );
	void handleOnKeyRelease(int KeyCode);
	void moveLeft();
	void moveRight();
	void jump();
	void sit();
	void stand();
	void hit();
	void beginFight();

	
	// Inherited via GameObject
	void setState(int state);
	virtual void update(DWORD dt, vector<LPGameObject> *coObject = nullptr);
	virtual void render() override;
	virtual Box getBoundingBox() override;

};

