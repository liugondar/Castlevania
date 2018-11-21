#include "StageLv1.h"
#include "BigCandle.h"


StageLv1::StageLv1()
{
	StageLv1::loadContent();
}


StageLv1::~StageLv1()
{
}

void StageLv1::render()
{
	auto game = Game::getInstance();
	const auto texture = TextureManager::getInstance()->get(ID_TEX_BACKGROUND_LV1);
	game->draw(0, 60, texture, 0, 0, SCENE_WIDTH, 384, 255);


	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}

	auto index = -1;
	for (auto& item : items) {
		index++;
		item->render();
	}

	this->simon->render();

	for (auto& brick : bricks) {
		brick->render();
	}
}

void StageLv1::update(DWORD dt)
{
	simon->update(dt, &bricks, &gameObjects, &items);
	for (auto& item : items)
	{
		item->update(dt, &bricks);
	}

	updateCamera(dt);
}

void StageLv1::loadContent()
{
	auto simon = new Simon();

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
}

void StageLv1::updateCamera(DWORD dt) const
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


void StageLv1::onKeyDown(int keyCode) 
{
	simon->handleOnKeyDown(keyCode);
}

void StageLv1::onKeyUp(int keyCode) 
{
	simon->handleOnKeyRelease(keyCode);
}

void StageLv1::keyState(BYTE* states) 
{
	simon->handleOnKeyPress(states);
}

void StageLv1::add(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void StageLv1::addBrick(Brick* brick)
{
	bricks.push_back(brick);
}

void StageLv1::addItem(GameObject* item)
{
	items.push_back(item);
}

void StageLv1::addSimon(Simon* simon)
{
	this->simon = simon;
}

void StageLv1::removeGameObject(int id)
{
}

void StageLv1::removeGameObject(GameObject* gameObject)
{
	int index = -1;
	for (auto i = gameObjects.begin(); i < gameObjects.end(); )
	{
		index++;
		if (index == gameObjects.size()) break;
		if (gameObjects[index] == gameObject) {
			i = gameObjects.erase(i);
			delete gameObject;
		}
		else {
			++i;
		}
	}

	index = -1;
	for (auto i = items.begin(); i < items.end(); )
	{
		index++;
		if (index == items.size()) break;
		if (items[index] == gameObject) {
			i = items.erase(i);
			delete gameObject;
		}
		else {
			++i;
		}
	}
}

void StageLv1::removeItem(GameObject* item)
{
	auto index = -1;
	for (auto i = items.begin(); i < items.end(); )
	{
		index++;
		if (index == items.size()) break;
		if (items[index] == item) {
			i = items.erase(i);
			delete item;
		}
		else {
			++i;
		}
	}
}
