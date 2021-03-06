﻿#include "TileMap.h"
#define SCREEN_WIDTH 640


TileMap::TileMap(const LPCWSTR filePathData, 
	const int mapWidth, const int mapHeight, 
	const int tileWidth, const int tileHeight)
{

	this->dataPath = filePathData;

	sprites = SpriteManager::getInstance();

	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	totalRow = mapHeight / tileHeight;
	totalCol = mapWidth / tileWidth;
}

void TileMap::loadTileMap(LPDIRECT3DTEXTURE9 texTileMap)
{

	D3DSURFACE_DESC surfaceDesc;
	const auto level = 0;
	texTileMap->GetLevelDesc(level, &surfaceDesc);

	const int totalTextureRow = surfaceDesc.Height / tileHeight;
	const int totalTextureCol = surfaceDesc.Width / tileWidth;

	auto idSprite = 1;

	for (auto i = 0; i < totalTextureRow; i++)
	{
		for (auto j = 0; j < totalTextureCol; j++)
		{
			sprites->add(idSprite, tileWidth * j, tileHeight * i, tileWidth * (j + 1), 
				tileHeight * (i + 1), texTileMap);
			idSprite += 1;
		}
	}
	fstream fs;
	fs.open(dataPath, ios::in);

	if (fs.fail())
	{
		DebugOut(L"[ERROR] TileMap::Load_MapData failed ");
		fs.close();
		return;
	}

	string line;

	while (!fs.eof())
	{
		getline(fs, line);
		vector<int> numInLine;
		stringstream ss(line);
		int n;

		while (ss >> n) {
			numInLine.push_back(n);
		}
		matrix.push_back(numInLine);
	}


	fs.close();
}


void TileMap::draw()
{
	float xCam, yCam;
	Game::getInstance()->getCameraPosition(xCam, yCam);

	auto startColToDraw = static_cast<int>(xCam) / 32;
	auto endColToDraw = static_cast<int>(xCam + SCREEN_WIDTH) / 32;
	if (endColToDraw >= totalCol) endColToDraw = totalCol-1;


	for (auto i = 0; i < totalRow; i++)
	{
		for (auto j = startColToDraw; j <= endColToDraw; j++)
		{
			// get position x,y to draw sprite ( depend on camera  x and y )
			// TODO: get position x  depend on yCam
			const auto x = tileWidth * (j - startColToDraw) + xCam - static_cast<int>(xCam) % 32;
			const auto y = tileHeight * i + yCam +60;

			sprites->get(matrix[i][j])->draw(x, y);
		}
	}
}


TileMap::~TileMap()
= default;
