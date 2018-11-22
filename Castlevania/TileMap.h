#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "TextureManager.h"
#include "SpriteManager.h"
#include "Debug.h"
class TileMap
{
	int Id;
	int mapWidth;
	int mapHeight;
	int totalRow;
	int totalCol;
	int tileWidth;
	int tileHeight;
	LPCWSTR texturePath;
	LPCWSTR dataPath;
public:
	vector<vector<int>> matrix;
	SpriteManager * sprites;
	TileMap(LPCWSTR filePathData, int mapWidth, int mapHeight, int tileWidth, int tileHeight);
	void loadResources(LPDIRECT3DTEXTURE9 texTileMap);
	void draw(float x,float y);
	int getMapWidth() const { return mapWidth; }


	~TileMap();
};

