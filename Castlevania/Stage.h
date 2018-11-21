#pragma once
#include <Windows.h>
#include "Simon.h"

class GameObject;
constexpr auto SCENE_WIDTH = 1536;
constexpr auto SCENE_HEIGHT = 384;

class Stage
{
public:
	Stage();
	virtual ~Stage();

	virtual void render()=0;
	virtual void update(DWORD dt)=0;
	virtual void loadContent()=0;
	virtual void onKeyDown(int keyCode)=0 ;
	virtual void onKeyUp(int keyCode) =0 ;
	virtual void keyState(BYTE *states) = 0;

	virtual void add(GameObject* gameObject) = 0;
	virtual void addItem(GameObject* gameObject)=0;
	virtual void removeGameObject(GameObject* gameObject)=0;
	virtual void removeItem(GameObject* item) = 0;
};

