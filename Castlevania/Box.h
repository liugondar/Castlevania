#pragma once

struct Box
{
	float left;
	float top;

	float right;
	float bottom;

	float vx;
	float vy;

	float dx;
	float dy;
	float dt;
	Box();
	Box(float x,float y,float w,float h);
};
