#pragma once
#include "Game.h"
#include "Brick.h"
#include "Simon.h"
#include "BigCandle.h"
using namespace std;

constexpr auto SCENE_WIDTH = 1536;
constexpr auto SCENE_HEIGHT = 384;

class GameObjectManger
{
private:
	static GameObjectManger* instance;
	Simon* simon;
	vector<GameObject *> bricks;
	vector <GameObject*> gameObjects;
public:
	static GameObjectManger* getInstance() {
		if (instance == nullptr) instance = new GameObjectManger();
		return instance;
	}

	// util methods
	void updateCamera(DWORD dt);

	// event methods
	void onKeyDown(int KeyCode);
	void onKeyUp(int KeyCode);
	void keyState(BYTE *states);
	void render();
	void update(DWORD dt);

	// mananger objects methods
	void loadGameObjects();

	void add(GameObject* gameObject) {
		gameObjects.push_back(gameObject);
	}
	
	void addBrick(Brick* brick) {
		bricks.push_back(brick);
	}

	void addSimon(Simon * simon) {
		this->simon = simon;
	}

	vector<GameObject*> getBricks() { return bricks; }
};

