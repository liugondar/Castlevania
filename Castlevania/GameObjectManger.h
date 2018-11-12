#pragma once
#include "Game.h"
#include "Brick.h"
#include "Simon.h"
using namespace std;

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
	void render();
	void update(DWORD dt);

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

