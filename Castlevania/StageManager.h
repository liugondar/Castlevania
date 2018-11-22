#pragma once
#include "Stage.h"
#include "StageLv1.h"

class StageManager
{
	static StageManager* instance;
	Stage* currentStage = nullptr;
	Stage* preStage = nullptr;
public:
	static StageManager* getInstance() {
		if (instance == nullptr) instance = new StageManager();
		return instance;
	};

	~StageManager();

	Stage* getCurrentState() const { return currentStage; }
	void init() { currentStage = new StageLv1(); }
	void setStage(Stage* newStage) { preStage = currentStage; currentStage = newStage; }
	void render() const
	{
		currentStage->render();
	}
	void update(const DWORD dt) const { currentStage->update(dt); }
	void onKeyDown(int keyCode) const { currentStage->onKeyDown(keyCode); }
	void onKeyUp(int keyCode) const { currentStage->onKeyUp(keyCode); }
	void keyState(BYTE *states) const { currentStage->keyState(states); }

	void add(GameObject* gameObject) const { currentStage->add(gameObject); }
	void remove(GameObject* gameObject)const { currentStage->remove(gameObject); }
};

