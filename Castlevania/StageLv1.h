#pragma once
#include "Stage.h"
#include "Game.h"
#include "GameObject.h"
#include "Simon.h"

constexpr auto SCENE1_WIDTH = 1536;
constexpr auto SCENE1_HEIGHT = 384;

class StageLv1: public Stage
{
	vector<GameObject *> bricks;
	vector <GameObject*> gameObjects;
	vector <GameObject* > canHitObjects;
	vector <GameObject* > coObjects;
	vector <GameObject*> items;
public:
public:
	StageLv1();
	~StageLv1();
	void loadContent() override;

	// event methods
	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;
	void keyState(BYTE *states) override;
	void render() override;
	void update(DWORD dt) override;

	// manager objects methods

	void add(GameObject* gameObject) override;
	void addCanHitObject(GameObject* ob) { canHitObjects.push_back(ob); }
	void addSimon(Simon* simon);
	void remove(GameObject* gameObject) override;
};

