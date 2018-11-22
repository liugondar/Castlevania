#include "StageLv1.h"
#include "BigCandle.h"
#include "Brick.h"


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
	float camX, camY;
	game->getCameraPosition(camX, camY);

	tileMap->draw(camX, camY + 60);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}

	for (auto i = 0; i < canHitObjects.size(); i++)
	{
		auto canHitOb = canHitObjects[i];
		canHitOb->render();
	}
	this->simon->render();

	for (auto i = 0; i < coObjects.size(); i++)
	{
		auto coOb = coObjects[i];
		coOb->render();
	}

}

void StageLv1::update(DWORD dt)
{
	simon->update(dt, &coObjects, &canHitObjects);

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
		add(brick);
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

	const auto texMap = TextureManager::getInstance()->get(ID_TEX_MAP_LV1);

	tileMap = new TileMap(L"Resources\\sprites\\background\\map1.txt", 1536, 384, 32, 32);
	tileMap->loadResources(texMap);
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
	const auto type = gameObject->getType();
	if (type == GameObjectType::coObject) {
		addObjectToList(gameObject, coObjects);
	}
	else if (type == GameObjectType::item)
	{
		addObjectToList(gameObject, coObjects);
		addObjectToList(gameObject, items);
	}
	else if (type == GameObjectType::brick)
	{
		addObjectToList(gameObject, coObjects);
		addObjectToList(gameObject, bricks);
	}
	else if (type == GameObjectType::canHitObject) addObjectToList(gameObject,canHitObjects);
	else gameObjects.push_back(gameObject);
}


void StageLv1::addSimon(Simon* simon)
{
	this->simon = simon;
}

void StageLv1::remove(GameObject* gameObject)
{
	const auto type = gameObject->getType();

	if (type == GameObjectType::coObject) {
		removeObjectFromList(gameObject,coObjects);
	}
	else if(type== GameObjectType::item)
	{
		removeObjectFromList(gameObject,coObjects);
		removeObjectFromList(gameObject,items);
	}
	else if (type == GameObjectType::brick)
	{
		removeObjectFromList(gameObject, bricks);
	}
	else if(type==GameObjectType::canHitObject)
	{
		removeObjectFromList(gameObject, canHitObjects);
	}
	else
	{
		removeObjectFromList(gameObject,gameObjects);
	}

		delete(gameObject);
}
