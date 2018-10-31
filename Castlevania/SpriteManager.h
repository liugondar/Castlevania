#pragma once
#include "Game.h"
#include "Sprite.h"
using namespace std;


constexpr auto SPRITE_MARIO_FACE_LEFT_1 = 10001;
constexpr auto SPRITE_MARIO_FACE_LEFT_2 = 10002;
constexpr auto SPRITE_MARIO_FACE_LEFT_3 = 10003;

constexpr auto SPRITE_MARIO_FACE_RIGHT_1 = 10011;
constexpr auto SPRITE_MARIO_FACE_RIGHT_2 = 10012;
constexpr auto SPRITE_MARIO_FACE_RIGHT_3 = 10013;

constexpr auto SPRITE_BRICK = 20001;
constexpr auto SPRITE_GOOMBA_GO_LEFT = 30001;
constexpr auto SPRITE_GOOMBA_GO_RIGHT= 30011;
constexpr auto SPRITE_GOOMBA_DIE= 30021;

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

