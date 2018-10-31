#include "SpriteManager.h"

SpriteManager * SpriteManager::instance = NULL;

void SpriteManager::add(int id, int left, int top, int right,int bottom, LPDIRECT3DTEXTURE9 texture)
{
	auto s = new Sprite(id,left,top,right,bottom,texture);
	sprites[id] = s;
}
