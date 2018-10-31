#pragma once
#include "Game.h"
using namespace std;

constexpr auto ID_TEX_MARIO = 0;
constexpr auto ID_TEX_ENEMY = 10;
constexpr auto ID_TEX_MISC = 20;
constexpr auto ID_TEX_BBOX = -100;		//

class TextureManager
{
private:
	static TextureManager* instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	TextureManager();
	~TextureManager();

	void add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);

	LPDIRECT3DTEXTURE9 get(unsigned int i) {
		return textures[i];
	}

	static TextureManager* getInstance() {
		if (instance == NULL) instance = new TextureManager();
		return instance;
	}
};

