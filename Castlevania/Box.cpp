#include "Box.h"

Box::Box()
{
	left = top = right = bottom = vx = vy = 0.f;
}

Box::Box(float x, float y, float w, float h)
{
	this->left = x;
	this->top = y;
	right = w;
	bottom = h;
	vx = 0.f;
	vy = 0.f;
}
