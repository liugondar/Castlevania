#pragma once
#include "Game.h"
#include "Constants.h"
#include "Sprite.h"
using namespace std;


class SpriteManager
{
private:
	static SpriteManager * instance;

	unordered_map<int, Sprite* > sprites;

	LPDIRECT3DTEXTURE9 texture;
public:
	void add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);

	Sprite* get(int id) {
		return sprites[id];
	}

	static SpriteManager * getInstance() {
		if (instance == NULL) instance = new SpriteManager();
		return instance;
	}
};

