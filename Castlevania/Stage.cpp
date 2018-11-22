#include "Stage.h"



Stage::Stage()
{
}


Stage::~Stage()
= default;

void Stage::updateCamera(const DWORD dt) const
{
	auto game = Game::getInstance();
	float simonX, simonY, xCamera, yCamera, simonVx, simonVy;
	simon->getPosition(simonX, simonY);
	simon->getSpeed(simonVx, simonVy);
	game->getCameraPosition(xCamera, yCamera);

	auto newCameraPositionX = xCamera + simonVx * dt;
	// check if new camera postion is out of box
	if (newCameraPositionX + SCREEN_WIDTH > sceneWidth)
		newCameraPositionX = sceneWidth - SCREEN_WIDTH;
	if (newCameraPositionX < 0) newCameraPositionX = 0;


	if (simonVx >= 0) {
		if (simonX >= (0 + SCREEN_WIDTH) / 2)
			game->setCameraPosition(newCameraPositionX, yCamera);
	}
	else {
		const auto middlePointOfEndScreen = (sceneWidth - SCREEN_WIDTH) + (SCREEN_WIDTH / 2);
		if (simonX <= middlePointOfEndScreen)
			game->setCameraPosition(newCameraPositionX, yCamera);
	}
}

void Stage::addObjectToList(GameObject* gameObject, vector<GameObject*> &container)
{
	container.push_back(gameObject);
}

void Stage::removeObjectFromList(GameObject* gameObject, vector<GameObject*>& container) const
{
	auto index = -1;
	for (auto i = container.begin(); i < container.end(); )
	{
		index++;
		if (index == container.size()) break;
		if (container[index] == gameObject) {
			i = container.erase(i);
		}
		else {
			++i;
		}
	}
}
