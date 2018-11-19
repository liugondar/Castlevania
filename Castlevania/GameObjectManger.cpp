#include "GameObjectManger.h"
#include "BigCandle.h"
#include "DaggerItem.h"
#include "DaggerSubWeapon.h"
#include "BurnEffect.h"
#include "CollisionEffect.h"

class DaggerItem;
GameObjectManger* GameObjectManger::instance = nullptr;

void GameObjectManger::updateCamera(const DWORD dt) const
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
		const auto middlePointOfEndScreen = (SCENE_WIDTH - SCREEN_WIDTH) + (SCREEN_WIDTH / 2);
		if (simonX <= middlePointOfEndScreen)
			game->setCameraPosition(newCameraPositionX, yCamera);
	}
}

void GameObjectManger::onKeyDown(const int keyCode) const
{
	simon->handleOnKeyDown(keyCode);
}

void GameObjectManger::onKeyUp(const int keyCode) const
{
	simon->handleOnKeyRelease(keyCode);
}

void GameObjectManger::keyState(BYTE * states) const
{
	simon->handleOnKeyPress(states);
}

void GameObjectManger::loadGameObjects()
{
	auto simon = new Simon();

	simon->setId(SIMON_ID);
	simon->setPosition(10.f, 100.f);
	simon->setState(SimonState::idle);
	simon->setBoundingGame(SCENE_WIDTH, SCENE_HEIGHT);

	addSimon(simon);


	for (auto i = 0; i < 100; i++)
	{
		auto brick = new Brick();
		brick->setPosition(0 + i * 16.0f, LV1_GROUND_Y);
		addBrick(brick);
	}

	auto candle = new BigCandle();
	candle->setPosition(190, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setItemContain(ItemBigCandleContain::heart);
	add(candle);

	candle = new BigCandle();
	candle->setPosition(448 + 64, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setItemContain(ItemBigCandleContain::whipUpgrade);
	add(candle);

	candle = new BigCandle();
	candle->setPosition(702, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setItemContain(ItemBigCandleContain::whipUpgrade);
	add(candle);

	candle = new BigCandle();
	candle->setPosition(960 + 64, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setItemContain(ItemBigCandleContain::heart);
	add(candle);

	candle = new BigCandle();
	candle->setPosition(1199, LV1_GROUND_Y - BIG_CANDLE_HEIGHT);
	candle->setItemContain(ItemBigCandleContain::dagger);
	add(candle);

	auto burn = new BurnEffect();
	burn->setPosition(100, 100);
	add(burn);

	auto coolisionEffect = new CollisionEffect();
	coolisionEffect->setPosition(100, 200);
	add(coolisionEffect);
}

void GameObjectManger::add(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void GameObjectManger::addBrick(Brick* brick)
{
	bricks.push_back(brick);
}

void GameObjectManger::addItem(Item* item)
{
	items.push_back(item);
}

void GameObjectManger::addSimon(Simon* simon)
{
	this->simon = simon;
}


void GameObjectManger::removeGameObject(const int id)
{
	int index = -1;
	for (auto i = gameObjects.begin(); i < gameObjects.end(); )
	{
		index++;
		if (index == gameObjects.size()) break;
		if (gameObjects[index]->getId() == id) {
			i = gameObjects.erase(i);
		}
		else {
			++i;
		}
	}
}

void GameObjectManger::removeGameObject(GameObject * gameObject)
{
	int index = -1;
	for (auto i = gameObjects.begin(); i < gameObjects.end(); )
	{
		index++;
		if (index == gameObjects.size()) break;
		if (gameObjects[index] == gameObject) {
			i = gameObjects.erase(i);
		}
		else {
			++i;
		}
	}
}

void GameObjectManger::removeItem(GameObject * item)
{
	auto index = -1;
	for (auto i = items.begin(); i < items.end(); )
	{
		index++;
		if (index == items.size()) break;
		if (items[index] == item) {
			i = items.erase(i);
		}
		else {
			++i;
		}
	}
}

void GameObjectManger::render()
{
	auto game = Game::getInstance();
	const auto texture = TextureManager::getInstance()->get(ID_TEX_BACKGROUND_LV1);
	game->draw(0, 60, texture, 0, 0, SCENE_WIDTH, 384, 255);



	for (auto& gameObject : gameObjects)
	{
		gameObject->render();
	}
	this->simon->render();
	for (auto& brick : bricks)
	{
		brick->render();
	}
	for (auto& item : items)
	{
		item->render();
	}


}

void GameObjectManger::update(const DWORD dt)
{
	simon->update(dt, &bricks, &gameObjects, &items);
	for (auto& item : items)
	{
		item->update(dt, &bricks);
	}

	updateCamera(dt);
}
