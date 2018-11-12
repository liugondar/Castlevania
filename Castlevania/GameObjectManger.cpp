#include "GameObjectManger.h"

GameObjectManger* GameObjectManger::instance = nullptr;

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
	Simon::addAnimation(ANIMATION_SIMON_WALKING_RIGHT);
	Simon::addAnimation(ANIMATION_SIMON_WALKING_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_IDLE_FACE_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_IDLE_FACE_RIGHT);
	Simon::addAnimation(ANIMATION_SIMON_SIT_FACE_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_SIT_FACE_RIGHT);
	Simon::addAnimation(ANIMATION_SIMON_HITTING_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_HITTING_RIGHT);

	simon->setPosition(10.f, 100.f);
	simon->setState(STATE_SIMON_IDLE);
	simon->setBoundingGame(SCENE_WIDTH, SCENE_HEIGHT);

	addSimon(simon);

	Brick::addAnimation(ANIMATION_BRICK_IDLE);

	Whip::addAnimation(ANIMATION_WHIP_LV1_LEFT);
	Whip::addAnimation(ANIMATION_WHIP_LV1_RIGHT);
	BigCandle::addAnimation(ANIMATION_BIG_CANDLE_IDLE);

	for (int i = 0; i < 100; i++)
	{
		auto brick = new Brick();
		brick->setPosition(0 + i * 16.0f, LV1_GROUND_Y);
		addBrick(brick);
	}

	for (int i = 0; i < 20; i++)
	{
		auto candle = new BigCandle();
		candle->setPosition(0 + i * 75.f, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
		add(candle);
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
}

void GameObjectManger::update(DWORD dt)
{
	simon->update(dt, &bricks, &gameObjects);
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
