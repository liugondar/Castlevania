#pragma once
#include "Stage.h"
#include "Game.h"
#include "Brick.h"
#include "Simon.h"



class StageLv1: public Stage
{
	Simon* simon{};
	vector<GameObject *> bricks;
	vector <GameObject*> gameObjects;
	vector <GameObject*> items;
public:
public:
	StageLv1();
	~StageLv1();
	void loadContent() override;

	// util methods
	void updateCamera(DWORD dt) const;

	// event methods
	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;
	void keyState(BYTE *states) override;
	void render() override;
	void update(DWORD dt) override;

	// manager objects methods

	void add(GameObject* gameObject) override;
	void addBrick(Brick* brick);
	void addItem(GameObject* item) override;
	void addSimon(Simon* simon);
	void removeGameObject(int id);
	void removeGameObject(GameObject* gameObject) override;
	void removeItem(GameObject* item) override;

	vector<GameObject*> getBricks() const { return bricks; }
};

