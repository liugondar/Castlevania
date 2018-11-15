#include "GameObjectManger.h"

GameObjectManger* GameObjectManger::instance = nullptr;

void GameObjectManger::updateCamera(DWORD dt)
{
	auto game = Game::getInstance();
	float simonX, simonY, xCamera, yCamera, simonVx, simonVy;
	simon->getPosition(simonX, simonY);
	simon->getSpeed(simonVx, simonVy);
	game->getCameraPosition(xCamera, yCamera);

	auto newCameraPositionX = xCamera + simonVx * dt;
	// check if new camera postion is out of box
	if (newCameraPositionX + SCREEN_WIDTH > SCENE_WIDTH)
		newCameraPositionX = SCENE_WIDTH - SCREEN_WIDTH;
	if (newCameraPositionX < 0) newCameraPositionX = 0;


	if (simonVx >= 0) {
		if (simonX >= (0 + SCREEN_WIDTH) / 2)
			game->setCameraPosition(newCameraPositionX, yCamera);
	}
	else {
		auto middlePointOfEndScreen = (SCENE_WIDTH - SCREEN_WIDTH) + (SCREEN_WIDTH / 2);
		if (simonX <= middlePointOfEndScreen)
			game->setCameraPosition(newCameraPositionX, yCamera);
	}
}

void GameObjectManger::onKeyDown(int KeyCode)
{
	simon->handleOnKeyDown(KeyCode);
}

void GameObjectManger::onKeyUp(int KeyCode)
{
	simon->handleOnKeyRelease(KeyCode);
}

void GameObjectManger::keyState(BYTE * states)
{
	simon->handleOnKeyPress(states);
}

void GameObjectManger::loadGameObjects()
{
	auto simon = new Simon();
	Simon::addAnimation(ANIM_SIM_WALKING_RIGHT);
	Simon::addAnimation(ANIM_SIM_WALKING_LEFT);
	Simon::addAnimation(ANIM_SIM_IDLE_FACE_LEFT);
	Simon::addAnimation(ANIM_SIM_IDLE_FACE_RIGHT);
	Simon::addAnimation(ANIM_SIM_SIT_FACE_LEFT);
	Simon::addAnimation(ANIM_SIM_SIT_FACE_RIGHT);
	Simon::addAnimation(ANIM_SIM_HIT_LEFT);
	Simon::addAnimation(ANIM_SIM_HIT_RIGHT);
	Simon::addAnimation(ANIM_SIM_HIT_WHEN_SIT_LEFT);
	Simon::addAnimation(ANIM_SIM_HIT_WHEN_SIT_RIGHT);

	simon->setId(simonId);
	simon->setPosition(10.f, 100.f);
	simon->setState(STATE_SIMON_IDLE);
	simon->setBoundingGame(SCENE_WIDTH, SCENE_HEIGHT);

	addSimon(simon);

	Brick::addAnimation(ANIMATION_BRICK_IDLE);

	Whip::addAnimation(ANIMATION_WHIP_LV1_LEFT);
	Whip::addAnimation(ANIMATION_WHIP_LV1_RIGHT);
	BigCandle::addAnimation(ANIMATION_BIG_CANDLE_IDLE);
	Item::addAnimation(ANIM_HEART_ITEM_IDLE);

	for (int i = 0; i < 100; i++)
	{
		auto brick = new Brick();
		brick->setPosition(0 + i * 16.0f, LV1_GROUND_Y);
		addBrick(brick);
	}

	auto candle = new BigCandle();
	candle->setPosition(0 + 5 * 75.f, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setId(bigCandle1Id);
	add(candle);

	candle = new BigCandle();
	candle->setPosition(0 + 6 * 75.f, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setId(bigCandle2Id);
	add(candle);

	candle = new BigCandle();
	candle->setPosition(0 + 7 * 75.f, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setId(bigCandle3Id);
	add(candle);
}

void GameObjectManger::removeGameObject(int id)
{
	int index = -1;
	for (auto i = gameObjects.begin(); i < gameObjects.end(); )
	{
		index++;
		if (index == gameObjects.size()) break;
		if (gameObjects[index]->getId()==id) {
			i = gameObjects.erase(i);
		}
		else {
			++i;
		}
	}
}

void GameObjectManger::render()
{
	auto game = Game::getInstance();
	auto texture = TextureManager::getInstance()->get(ID_TEX_BACKGROUND_LV1);
	game->draw(0, 60, texture, 0, 0, SCENE_WIDTH, 384, 255);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}
	this->simon->render();
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->render();
	}
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->render();
	}
}

void GameObjectManger::update(DWORD dt)
{
	simon->update(dt, &bricks, &gameObjects);
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->update(dt,&bricks);
	}
	updateCamera(dt);
}
