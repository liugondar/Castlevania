#pragma once
#include <Windows.h>
#include "TileMap.h"
#include "Simon.h"

class Stage
{
protected:
	TileMap * tileMap;
	Simon* simon{};
	int sceneWidth;
	int sceneHeight;
public:
	Stage();
	virtual ~Stage();

	virtual void render()=0;
	virtual void update(DWORD dt)=0;
	virtual void loadContent()=0;
	virtual void onKeyDown(int keyCode)=0 ;
	virtual void onKeyUp(int keyCode) =0 ;
	virtual void keyState(BYTE *states) = 0;

	void updateCamera(DWORD dt) const;
	// add object to game objects list
	virtual void add(GameObject* gameObject) = 0;
	void addObjectToList(GameObject* gameObject, vector<GameObject*> &container);
	// add object to item list
	virtual void remove(GameObject* gameObject)=0;
	void removeObjectFromList(GameObject* gameObject, vector<GameObject*>& container) const;

};

