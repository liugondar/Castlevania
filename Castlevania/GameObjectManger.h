#pragma once
#include "Game.h"
#include "Brick.h"
#include "Simon.h"
using namespace std;

constexpr auto SCENE_WIDTH = 1536;
constexpr auto SCENE_HEIGHT = 384;
constexpr auto SIMON_ID = 1;
constexpr auto BIG_CANDLE1_ID = 2;
constexpr auto BIG_CANDLE2_ID= 3;
constexpr auto BIG_CANDLE3_ID= 4;

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

	void add(GameObject* gameObject) {
		gameObjects.push_back(gameObject);
	}
	
	void addBrick(Brick* brick) {
		bricks.push_back(brick);
	}

	void addItem(Item* item) {
		items.push_back(item);
	}

	void addSimon(Simon * simon) {
		this->simon = simon;
	}

	void removeGameObject(int id);
	void removeGameObject(GameObject* gameObject);
	void removeItem(GameObject* item);

	vector<GameObject*> getBricks() const { return bricks; }
};

