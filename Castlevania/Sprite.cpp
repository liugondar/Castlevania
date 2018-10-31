#include "Sprite.h"


Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = texture;
}


void Sprite::draw(float x, float y)
{
	if (texture) {
	auto game = Game::getInstance();
	game->draw(x, y, texture, left, right, top, bottom);

	}
}