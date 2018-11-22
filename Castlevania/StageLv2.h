#pragma once
#include "Stage.h"
constexpr auto SCENE2_WIDTH = 1536;
constexpr auto SCENE2_HEIGHT = 384;

class StageLv2:public Stage
{
	vector<GameObject *> bricks;
	vector <GameObject*> gameObjects;
	vector <GameObject* > canHitObjects;
	vector <GameObject* > coObjects;
	vector <GameObject*> items;
public:
	StageLv2();
	~StageLv2();
	void render() override;
	void update(DWORD dt) override;
	void loadContent() override;
	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;
	void keyState(BYTE* states) override;
	void add(GameObject* gameObject) override;
	void remove(GameObject* gameObject) override;
};

