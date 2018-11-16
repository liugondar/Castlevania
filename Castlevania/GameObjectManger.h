#pragma once
#include "Game.h"
#include "Brick.h"
#include "Simon.h"
using namespace std;

constexpr auto SCENE_WIDTH = 1536;
constexpr auto SCENE_HEIGHT = 384;
constexpr auto SIMON_ID = 1;

class GameObjectManger
{
private:
	static GameObjectManger* instance;
	Simon* simon{};
	vector<GameObject *> bricks;
	vector <GameObject*> gameObjects;
	vector <GameObject*> items;
public:
	static GameObjectManger* getInstance() {
		if (instance == nullptr) instance = new GameObjectManger();
		return instance;
	}

	// util methods
	void updateCamera(DWORD dt) const;

	// event methods
	void onKeyDown(int keyCode) const;
	void onKeyUp(int keyCode) const;
	void keyState(BYTE *states) const;
	void render();
	void update(DWORD dt);

	// manager objects methods
	void loadGameObjects();

	void add(GameObject* gameObject);
	void addBrick(Brick* brick);
	void addItem(Item* item);
	void addSimon(Simon* simon);
	void removeGameObject(int id);
	void removeGameObject(GameObject* gameObject);
	void removeItem(GameObject* item);

	vector<GameObject*> getBricks() const { return bricks; }
};

