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
	int mapWidth;
	int mapHeight;
	int totalRow;
	int totalCol;
	int tileWidth;
	int tileHeight;
	LPCWSTR dataPath;
	vector<vector<int>> matrix;
	SpriteManager * sprites;
public:
	TileMap(LPCWSTR filePathData, int mapWidth, int mapHeight, int tileWidth, int tileHeight);
	void loadTileMap(LPDIRECT3DTEXTURE9 texTileMap);
	void draw();


	~TileMap();
};

