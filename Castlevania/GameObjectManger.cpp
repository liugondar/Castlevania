#include "GameObjectManger.h"

GameObjectManger* GameObjectManger::instance = nullptr;

void GameObjectManger::render()
{
	auto game = Game::getInstance();
	 auto texture = TextureManager::getInstance()->get(ID_TEX_BACKGROUND_LV1);
	game->draw(0,60, texture, 0, 0, 1536, 384,255);


	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}
	this->simon->render();
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->render();
	}
}

void GameObjectManger::update(DWORD dt)
{
	simon->update(dt,&bricks);
}
